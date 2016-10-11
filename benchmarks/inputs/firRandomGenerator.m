clc;
clear;
clear all;

coeffs = [-0.0448093,  0.0322875,   0.0181163,   0.0087615,   0.0056797, ...
       0.0086685,  0.0148049,   0.0187190,   0.0151019,   0.0027594, ...
      -0.0132676, -0.0232561,  -0.0187804,   0.0006382,   0.0250536, ...
       0.0387214,  0.0299817,   0.0002609,  -0.0345546,  -0.0525282, ...
      -0.0395620,  0.0000246,   0.0440998,   0.0651867,   0.0479110, ...
       0.0000135, -0.0508558,  -0.0736313,  -0.0529380,  -0.0000709, ...
       0.0540186,  0.0766746,   0.0540186,  -0.0000709,  -0.0529380, ...
      -0.0736313, -0.0508558,   0.0000135,   0.0479110,   0.0651867, ...
       0.0440998,  0.0000246,  -0.0395620,  -0.0525282,  -0.0345546, ...
       0.0002609,  0.0299817,   0.0387214,   0.0250536,   0.0006382, ...
      -0.0187804, -0.0232561,  -0.0132676,   0.0027594,   0.0151019, ...
       0.0187190,  0.0148049,   0.0086685,   0.0056797,   0.0087615, ...
       0.0181163,  0.0322875,  -0.0448093
];

for id=1:2
    
    % reate a m-by-n array of random integer values drawn from a discrete uniform distribution 
    % on the set of numbers [imin imax]. Use the syntax, randi([imin imax],m,n).
    numbers = randi([-32767 32767], 1, 80);
    
    filename = sprintf('fir_input%d.txt', id);
    fileID = fopen(filename,'w');
    
    formatSpec = 'coeffs_%d + %f 0\n';
    for ii=1:length(coeffs)
        fprintf(fileID, formatSpec,ii,coeffs(ii));
    end
    fprintf(fileID, '\n');

    formatSpec = 'input_%d + %d 0\n';
    for ii=1:length(numbers)
        fprintf(fileID, formatSpec,ii,numbers(ii));
    end
    fprintf(fileID, '\n');

    fclose(fileID);
end

%% create floating point input 

% Generate a 1-by-80 column vector of uniformly distributed numbers 
% in the interval (-32767, 32767).
numbers = -32767 + 2 * 32767 * rand(1,80)

fileID = fopen('fir_input3.txt','w');

formatSpec = 'coeffs_%d + %f 0\n';
for ii=1:length(coeffs)
    fprintf(fileID, formatSpec,ii,coeffs(ii));
end
fprintf(fileID, '\n');

formatSpec = 'input_%d + %f 0\n';
for ii=1:length(numbers)
    fprintf(fileID, formatSpec,ii,numbers(ii));
end
fprintf(fileID, '\n');

fclose(fileID);
