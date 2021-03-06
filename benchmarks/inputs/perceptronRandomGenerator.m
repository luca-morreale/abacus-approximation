clc;
clear;
clear all;

learning_rate = 0.5;

for id=1:6
    
    if id < 4
        points = 500;
        max_iteration = 200;
    else
        points = 2000;
        max_iteration = 300;
    end
    
    % generates random data that can be lineary seperated (silent)
    % generate random function y = mx + n
    m = 2  * rand * sign(randn);   % in (-2,2)/0
    n = 10  * rand + 5;            % in (5,15)

    % generate random points
    x = 20 * rand(points,2);        % in ((0,20), (0,20))

    % tolerance
    tol = 0.5;

    % labeling
    f = [x, -ones(points,1)];
    for ii=1:size(f,1)
        y = m * f(ii,1) + n;
        if f(ii,2) > y + tol
            f(ii,3) = 1;
        elseif f(ii,2) < y - tol
            f(ii,3) = 0;
        else
            f(ii,1) = f(ii,1) + 2 * tol;
            f(ii,3) = 1;
        end    
    end   
    
    filename = sprintf('perceptron_input%d.txt', id);
    fileID = fopen(filename,'w');
    
    fprintf(fileID, 'LEARNINGRATE %f\n', learning_rate);
    fprintf(fileID, 'MAXITERATION %d\n', max_iteration);
    fprintf(fileID, 'SAMPLES %d\n', points);
    
    fprintf(fileID, 'targetsLength %f\n', points);
    fprintf(fileID, 'xLength %d\n', points);
    fprintf(fileID, 'yLength %d\n', points);
    fprintf(fileID, 'outputLength %d\n', 4);
    

    formatSpec = 'x_%d %f\n';
    for ii=1:size(f,1)
        fprintf(fileID, formatSpec,ii-1,f(ii, 1));
    end
    fprintf(fileID, '\n');

    formatSpec = 'y_%d %f\n';
    for ii=1:size(f,1)
        fprintf(fileID, formatSpec,ii-1,f(ii, 2));
    end
    fprintf(fileID, '\n');

    formatSpec = 'targets_%d %d\n';
    for ii=1:size(f,1)
        fprintf(fileID, formatSpec,ii-1,f(ii, 3));
    end
    fprintf(fileID, '\n');

    fclose(fileID);
end
