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

for id=1:6

    filename = sprintf('fir_input%d.txt', id);
    fileID = fopen(filename,'w');
    
    fprintf(fileID, 'filterlength 63\n');
    
    if id < 4
        len = 143;
        fprintf(fileID, 'inputLength 143\n\n');
    else
        len = randi([63+80 1000], 1, 1);
        fprintf(fileID, 'inputLength %d\n\n', len);
    end
    
    fprintf(fileID, 'coeffsLength %d\n\n', length(coeffs));

    formatSpec = 'coeffs_%d %f\n';
    for ii=1:length(coeffs)
        fprintf(fileID, formatSpec,ii-1,coeffs(ii));
    end
    fprintf(fileID, '\n');
    
    % Generate a 1-by-143 column vector of uniformly distributed numbers 
    % in the interval (-32767, 32767).
    numbers = -32767 + 2 * 32767 * rand(1,len);

    formatSpec = 'input_%d %f\n';
    for ii=1:length(numbers)
        fprintf(fileID, formatSpec,ii-1,numbers(ii));
    end
    fprintf(fileID, '\n');

    fclose(fileID);
end
