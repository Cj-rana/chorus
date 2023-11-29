% Boss Ce-2 Remake


clear;clc;

[in,Fs]=audioread('AcGtr.wav'); %reads file into array and gets length

Ts=1/Fs;

N = length(in);

%min and max delay times in Ms
timeMsMax=50/1000;

%convert into samples

tsMax=ceil(timeMsMax*Fs); %Max delay time

buffer = zeros(tsMax,1);

gain=0.5; %gain to make signal the same volume

t=(0:(N-1))*Ts; 


t=t(:);


%LFO params

rate=1; % Frequency Speed of LFO in Hz, 3.57Hz is max position in ce-2, 0.357 is min

depth=22.5; %max 23.04, is delay is from 5.12ms to 51.2ms, centre 28.16, range is 46.08 so +-23.04 both ways

shift=0;

out=zeros(N,1);
out2=zeros(N,1);
out3=zeros(N,1);



for n = 1:N


[out(n,1),buffer] = chorusFunction(in(n,1),buffer,Fs,n,...
depth,rate,shift);

out2(n,1)=out(n,1);

end


shift=45;

for n = 1:N


[out(n,1),buffer] = chorusFunction(in(n,1),buffer,Fs,n,...
depth,rate,shift);

out3(n,1)=((out(n,1)+out2(n,1)*gain)+in(n,1))*gain;




end



%tLfoMs = depth*sawtooth(2*pi*rate*t,0.5)+27.5;
%plot(t,tLfoMs);

plot(t,in,"--r",t,out,":b",t,out2,"-g");


xlabel('Time (sec.)');ylabel('Amplitude');
legend('Dry','Chorus 1','Chorus 2');

sound(out3,Fs);
