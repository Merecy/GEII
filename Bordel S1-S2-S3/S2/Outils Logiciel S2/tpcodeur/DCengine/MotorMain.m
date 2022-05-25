%% MOTORMain.m
%% N Boizot 03 / 2021

warning off
close all
clear variables
clc

% ---------------------- %
% ---   PARAMETERS   --- %


Baudrate = 19200 ; % defined in the arduino program.
MOTEUR.Data_Size = 10;
MOTEUR.Encoder_Resolution = 48*172; %% 172:1
% ---------------------- %

if exist('MotorSerial') 
    clear MotorSerial
end

Slist = serialportlist('available');


index = listdlg('PromptString','Sélectionner le port COM','SelectionMode','single','ListString',Slist);

%MotorSerial = serialport(Slist(1),'19200,n,8,1'); 

MotorSerial = serialport(Slist(index),Baudrate); % Windows OS

% MotorSerial = serialport(Slist(4),Baudrate);  % My MAC (As of march 2021)


disp(Slist(index)+' is connected');

flush(MotorSerial,'input');
flush(MotorSerial,'output');

% Assuming there's only one element nin Slist

% global MOTOR
% MOTEUR.Max_Num_Port = 10;
% MOTEUR.COM_PORT = 2;
% MOTEUR.Data_Size = 10;
% MOTEUR.Encoder_Resolution = 48*172; %% 172:1
% MOTEUR.Encoder_Resolution = 48;


% exec MOTORconvert_SyRen.sce; % Not Needed in Matlab
% exec MOTORmeasure.sce; % Not Needed in Matlab
% exec MOTORclean.sce; % Not Needed in Matlab
% exec MOTORcalcul.sce; % Not Needed in Matlab


%%%%%exec MOTORreset.sce;  % Deprecated function

% while MOTEUR.COM_PORT < MOTEUR.Max_Num_Port then
%     try 
%        MOTEUR.Handle = openserial(MOTEUR.COM_PORT,'19200,n,8,1');
%         sleep(2000);
%         mprintf('Available port COM'+msprintf('%i',MOTEUR.COM_PORT)+' detected\n');
%         Error = 0;
%     catch
%         MOTEUR.COM_PORT = MOTEUR.COM_PORT + 1;
%         Error = -1;
%     end
%     if Error == 0 then
%         break
%     end
% end

%  if Error == -1 then
%     disp('!! ERROR !! \nNo available COM port detected');
%     disp('Unplug and Plug ARDUINO then try again');
% else
%    mprintf('Port COM'+msprintf('%i',MOTEUR.COM_PORT)+' connected\n');
%    Clean();
%    Mode = x_choose(['Open Loop';'Closed Loop';'Reset'],['Choose Command Mode'],'Return');
%    Mode = x_choose(['Open Loop';'Closed Loop'],['Choose Command Mode']);
Mode = menu('Boucle ouverte ou boucle fermée','Boucle ouverte','Boucle fermée')

% 1 -> ouverte
% 2 -> fermée

%    Mode = x_choices('Toggle Menu',list(list('Mode',1,['Open Loop','Closed Loop'])));
    % Message = input('Enter your order(don`t forget ''''):\n''[Regulation]/[Sens de rotation ou consigne]/[PWM ou gain*10]''');
    % Trame = Convert(Message);
    
    
    
        % Trame = Convert(Mode);
   
    Trame = MotorInterpret(Mode,MOTEUR);
    disp('Begin simulation');
    Tab = MotorMeasure(Trame,MotorSerial);
    disp('End simulation');
    
    clear MotorSerial
        
%     
%     mprintf('Port COM'+msprintf('%i',MOTEUR.COM_PORT)+' closed\n');
%     
%     
%     
      Data = MotorCalcul(Tab,MOTEUR);
      save ('Measure.txt', 'Data', '-ascii')
      
    
      figure(1)
     subplot(311)
     plot(Data(:,1),Data(:,3),'LineWidth',1,'color', 'blue');
     xlabel('temps (ms)', 'fontsize', 12, 'color', 'blue');
     ylabel('position (°)', 'fontsize', 12, 'color', 'blue');
     
     subplot(312)
     plot(Data(:,1),Data(:,4),'LineWidth',1,'Color','blue');
     xlabel('temps (ms)', 'fontsize', 12, 'color', 'blue');
     ylabel('vitesse (tr/min)', 'fontsize', 12, 'color', 'blue');
    
    subplot(313)
    plot(Data(:,1),Data(:,2),'LineWidth',1,'Color','blue');
    xlabel('temps (ms)', 'fontsize', 12, 'color', 'blue');
    ylabel('u(t)', 'fontsize', 12, 'color', 'blue');
    

    
    %
    %
    %
    %

    
    % ---------------------------------- %
    % ------ Functions definitions ----- %
    % (Possible since R2016)
        
    
    
function Message = MotorInterpret(Mode,MOTEUR)
    Boucle = Mode-1;
    switch Boucle
        case 0
            PPM = inputdlg('u(t) in [-400;400]','Amplitude de l''échelon d''entrée',[1,35],{'0'});
            if length(PPM) == 0, error('Opération interrompue'), end
            PPM = cell2mat(PPM);
            PPM = 500 + floor(str2num(PPM));
            PPM = min(900,max(100,floor(PPM)));
            Message = [num2str(Boucle),num2str(PPM),'00000000'];
        case 1
            answer = inputdlg({'Consigne d''angle','Gain'},'Réglages boucle fermée',[1,35],{'0','0'});
                % ----- %
            Angle = str2num(cell2mat(answer(1)));
            Code = round(Angle * MOTEUR.Encoder_Resolution/360);
            Message_Code = num2str(Code,'%07d');
                % ----- %
            G = str2num(cell2mat(answer(2)));
            Gain = round(G * 360 / MOTEUR.Encoder_Resolution*1000);
            Message_Gain = num2str(Gain,'%05d');
            Message = [num2str(Boucle), Message_Code, Message_Gain];     
    end
    disp(Message);
end
    
    
    
function Data = MotorMeasure(Message,MotorSerial)
    write(MotorSerial,Message,'uint8');
    XP = tic;
    while toc(XP)<6
        % empty while loop that waits 6 sec.
    end;
    Data_Received = read(MotorSerial,MotorSerial.NumBytesAvailable,'string');
    if length(Data_Received) == 0 then
        warning('There''s no data to read');
        Data = 0;
    else
        Data_Separated = strsplit(Data_Received, '|');
        Data_Separated = Data_Separated(1:end-1);
        Data_Separated = split(Data_Separated,'/');
        Data = double(Data_Separated);   
        Data = squeeze(Data);
    %    Time = Data_Separated(:,1);
    %    PWM = Data_Separated(:,2);
    %    Code = Data_Separated(:,1);
    end
end
     

function Data_converted = MotorCalcul(Data,MOTEUR)
    Time = Data(:,1)/1e3;;
    Input = Data(:,2)-500;
    Position = (Data(:,3)-2^20)*360/MOTEUR.Encoder_Resolution;

    Variation_Position = diff(Position);
    Variation_Time =diff(Time);
    
    
    Speed = Variation_Position*60000./(Variation_Time*360);
    Speed = [0;Speed];

    Data_converted = [Time,Input,Position,Speed];   
    
end
