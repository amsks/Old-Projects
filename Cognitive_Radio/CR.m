    clc
    close all
    clear all
    
    t = 0:0.00001:0.001;
    Fc1 = 1000;
    Fc2 = 2000;
    Fc3 = 3000;
    Fc4 = 4000;
    Fc5 = 5000;
    Fs = 12000;
    y1 = 1; y2 = 0; y3 = 0; y4 = 0; y5 = 0; Y = 0; y = 0;
    
    x1 = cos(2*pi*1000*t);
  
    in_p = input('\nDo you want to enter first primary user Y/N ?  ','s');
   
    
    if(in_p == 'Y' | in_p == 'y')
        y1 = ammod(x1,Fc1,Fs);
        
    end
    
    in_p = input('Do you want to enter second primary user Y/N ?  ','s');
    
    if(in_p == 'Y' | in_p == 'y')
        y2 = ammod(x1,Fc2,Fs);
    
    end
        
    in_p = input('Do you want to enter third primary user Y/N ?  ','s');

    if(in_p == 'Y' | in_p == 'y')
        y3 = ammod(x1,Fc3,Fs);
       
    end

    in_p = input('Do you want to enter fourth primary user Y/N ? ','s');

    if(in_p == 'Y' | in_p == 'y')
        y4 = ammod(x1,Fc4,Fs);
    
    end

    in_p = input('Do you want to enter fifth primary user Y/N ?  ','s');
    
    if(in_p == 'Y' | in_p == 'y')
        y5 = ammod(x1,Fc5,Fs);
        
    end
    
    y = y1 + y2 + y3 + y4 + y5;
    
while(1)
    
        Pxx = periodogram(y);
        Hpsd = dspdata.psd(Pxx,'Fs',Fs);
        plot(Hpsd);
    
        
  in_p = input('\nDo you want to enter a secondary user Y/N ?  ','s');
 
    if(in_p == 'Y' | in_p == 'y')
    
        
    
        tp=0;
        chek1 = Pxx(25)*10000;
        chek2 = Pxx(46)*10000;
        chek3 = Pxx(62)*10000;
        chek4 = Pxx(89)*10000;
        chek5 = Pxx(105)*10000;
        
        if(chek1 < 8000)
            disp('Assigned to User 1 as it was not present.');
            y1 = ammod(x1,Fc1,Fs);
    

    elseif (chek2 < 8000)
            disp('Assigned to User 2 as it was not present.');
            y2 = ammod(x1,Fc2,Fs);
        
    
        elseif(chek3 < 8000)
            disp('Assigned to User 3 as it was not present.');
            y3 = ammod(x1,Fc3,Fs);
        
    
        elseif(chek4 < 8000)
            disp('Assigned to User 4 as it was not present.');
            y4 = ammod(x1,Fc4,Fs);
        

        elseif(chek5 < 8000)
            disp('Assigned to User 5 as it was not present.');
            y5 = ammod(x1,Fc5,Fs);
        else
            disp('all user slots in use. try again later,');
            tp=1;
        end
        
        figure
        y = y1 + y2 + y3 + y4 + y5 ;
        Pxx = periodogram(y);                   
        Hpsd = dspdata.psd(Pxx,'Fs',Fs);
        plot(Hpsd);
         
         %,,,,,,,,,,,slot empty operation,,,,,,,,,,,,,,
        if(tp==1)
        inp_t=input('do u want to empty a slot:     ','s');
        if(inp_t=='Y'|inp_t=='y')
            inp_t=input('which slot do u want to empty for ur entry:     ','s');
            switch(inp_t)
                
                case ('1')
                    y1=0;
                    disp('slot1 is fired');
                    y = y1 + y2 + y3 + y4 + y5;
                    Pxx = periodogram(y);                   
                    Hpsd = dspdata.psd(Pxx,'Fs',Fs);
                    plot(Hpsd);
                    %break;
                
                case('2')
                    y2=0;
                    disp('slot2 is fired');
                    y = y1 + y2 + y3 + y4 + y5;    
                    Pxx = periodogram(y);
                    Hpsd = dspdata.psd(Pxx,'Fs',Fs);
                    plot(Hpsd);
                    %break;
                
                case('3')
                    y3=0;
                    disp('slot3 is fired');
                    y = y1 + y2 + y3 + y4 + y5;
                    Pxx = periodogram(y);
                    Hpsd = dspdata.psd(Pxx,'Fs',Fs);
                    plot(Hpsd);
                    %break;
                
                case('4')
                    y4=0;
                    disp('slot4 is fired');
                    y = y1 + y2 + y3 + y4 + y5;
                    Pxx = periodogram(y);
                    Hpsd = dspdata.psd(Pxx,'Fs',Fs);
                    plot(Hpsd);
                    %break;
                
                case('5')
                     y5=0;
                    disp('slot5 is fired');
                    y = y1 + y2 + y3 + y4 + y5;
                    Pxx = periodogram(y);
                    Hpsd = dspdata.psd(Pxx,'Fs',Fs);
                    plot(Hpsd);
                    %break;
                
                otherwise disp('invalid slot entered');
                   %break;
            end  %switch end
        end
        end
        %////////////////////Adding Noise////////////////////
        inp_t=input('do u want to add noise: ','s');
        if(inp_t=='y'|inp_t=='Y')
        d = input('Enter the SNR in dB:   ');
        figure
        Y = awgn(y,d);
        Pxx1 = periodogram(Y);
        Hpsd = dspdata.psd(Pxx1,'Fs',Fs);
        plot(Hpsd);
        disp('adding noise');
        
        chek1 = Pxx1(25).*10000;
        chek2 = Pxx1(49).*10000;
        chek3 = Pxx1(62).*10000;
        chek4 = Pxx1(89).*10000;
        chek5 = Pxx1(105).*10000;

        if(chek1 < 8000)
            disp('User 1 is not present.');
        else
            disp('User 1 is present.');
        end

        if(chek2 < 8000)
            disp('User 2 is not present.');
            else
            disp('User 2 is present.');
        end

        if(chek3 < 8000)
            disp('User 3 is not present.');
            else
            disp('User 3 is present.');
        end

        if(chek4 < 8000)
            disp('User 4 is not present.');
            else
            disp('User 4 is present.');
        end

        if(chek5 < 8000)
            disp('User 5 is not present.');
        else
            disp('User 5 is present.');
        end
        
        end
        
        %%%%%%%%%%%%%%%%%%%%%%%Attenuating the signal%%%%%%%
        
        temp = input('Do you want to attenuate the signals? [Y/N]:    ','s');
        if(temp == 'Y' | temp == 'y')
        Yff=0;
        aF = input('Enter the percentage to attenuate the signal:   ');
        
        figure
        tem = aF/100;
        tm = 1-tem;
        Z = y.*tm;
        disp('attenuating');
        
        grid on
        plot(Z);
        
        figure
        
        Pxx4 = periodogram(Z);
        Hpsd = dspdata.psd(Pxx4,'Fs',Fs);
        plot(Hpsd);
        
        chek1 = Pxx4(25).*10000;
        chek2 = Pxx4(49).*10000;
        chek3 = Pxx4(62).*10000;
        chek4 = Pxx4(89).*10000;
        chek5 = Pxx4(105).*10000;

        if(chek1 < 8000)
            disp('User 1 is not present.');
        else
            disp('User 1 is present.');
        end

        if(chek2 < 8000)
            disp('User 2 is not present.');
            else
            disp('User 2 is present.');
        end

        if(chek3 < 8000)
            disp('User 3 is not present.');
            else
            disp('User 3 is present.');
        end

        if(chek4 < 8000)
            disp('User 4 is not present.');
            else
            disp('User 4 is present.');
        end

        if(chek5 < 8000)
            disp('User 5 is not present.');
        else
            disp('User 5 is present.');
        end

        
        end
        
    end
    
    %if rerun the program
    
    temp = input('Do you want to re-run the program? [Y/N]:    ','s');
    
     if(temp == 'Y' | temp == 'y')
         disp('\n\nEnter the users again.\n\n');
     else
         break;
     end
end
