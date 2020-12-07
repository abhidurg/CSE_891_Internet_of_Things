%% Read data.
[data, fs] = audioread('signal.wav');

%% Start your code here.
signal_start = 99340;
signal_end = 494496;
message_start = signal_end - 2 * 98784;
message_end = signal_end - 1 * 98784;
t = 0:1/fs:(message_end - message_start - 1)/fs;
data = bandpass(data, [18000, 22000], fs);

%% Carrier Demodulation
fc = 20000;
carrier = cos(2*pi*fc*t);

message_wave = data(message_start:message_end-1);
multiplied_message = message_wave .* carrier';
baseband = lowpass(multiplied_message, 20000, fs);

%% Hilbert transform to eliminate frequency shift
hb = hilbert(baseband);
shift_param = 0.6940;
shift = exp(2i * pi * shift_param / fs * (1:length(baseband)));
transform_hb = hb ./ shift';
baseband = imag(transform_hb);

%% BPSK Demodulation
f = 100;
BPSK = sin(2*pi*f*t);
multiplied_baseband = baseband .* BPSK';

demodulated_baseband = lowpass(multiplied_baseband, 50, fs);
demodulated_baseband(demodulated_baseband < 0) = 0;
demodulated_baseband(demodulated_baseband > 0) = 1;

msg = zeros(1,224);
for i=1:224
    msg(i) = mode(demodulated_baseband((i-1)*441+1:i*441));
end

%% Convert data bits to ascii characters
text_length = length(msg) / 8;
text_ascii = zeros(1, text_length);
for i = 1:text_length
    c_ascii = 0;
    c_bin = msg((i-1)*8+1:i*8);
    for j = 1:8
        c_ascii = c_ascii * 2 + c_bin(j);
    end
    text_ascii(i) = c_ascii;
end

disp(char(text_ascii));

%% Bit Error Rate
original = b'; % depends on variable b created from running transmitter.m
received = msg;
num_different_bits = sum(original~=received);
num_same_bits = sum(original==received);
num_total_bits = 224;
disp("Number of erroneous bits: ");
disp(num_different_bits);
disp("Bit error rate: ");
disp(num_different_bits/num_total_bits);
