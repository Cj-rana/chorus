% Boss Ce-2 Remake
% Vibrato + Dry signal=Chorus
%
% Input Variables
% in: single sample of input
% buffer: used to store delayed samples
% n: current sample number for LFO
%
% Depth: range of modulation (samples)
% Rate: speed of mod (freq, Hz)



function [out,buffer] = chorusFunction(in,buffer,Fs,n,...
    depth,rate,shift)

% Calculate lfo for current sample

t = (n-1)/Fs;

tLfoMs = depth*sawtooth(2*pi*rate*t,0.5)+shift; %for depth

% Determine indexes for circular buffer
len = length(buffer);
indexC = mod(n-1,len) + 1; % Current index in circular buffer

fracDelay = mod(n-tLfoMs-1,len) + 1; % Delay index in circular buffer

intDelay = floor(fracDelay); 

frac = fracDelay - intDelay;

nextSamp = mod(intDelay,len) + 1;

out = (1-frac) * buffer(intDelay,1) + ...
(frac) * buffer(nextSamp,1);

% Store the current output in appropriate index
buffer(indexC,1) = in;

