%{
# ARG:  pucRefX      Reference frame left top pointer. 
#       pucRefY      Reference frame left top pointer. 
#       pucCurX      Current   frame left top pointer. 
#       pucCurY      Current   frame left top pointer. 
#       piMvPos     Pointer of position indicated by result MV. 
#       iWidth      Width of the frame. 
#       iLeft       Search area left position. 
#       iRight      Search area right position. 
#       iTop        Search area top position.
#       iBottom     Search area bottom position. 
#       iHpos       Current block left position in the frame. 
#       iVpos       Current block top position in the frame. 
%}

% create a m-by-n array of random integer values drawn from a discrete uniform distribution 
% on the set of numbers [imin imax]. Use the syntax, randi([imin imax],m,n).


for id=1:3
    
    
    filename = sprintf('block_input%d.txt', id);
    fileID = fopen(filename,'w');
    
    %pucRefX = 0;
    %pucRefY = 0;
    %pucCurX = 0;
    %pucCurY = 0;
    piMvPos = 0;
    iWidth  = randi([100 150], 1, 1);
    iLeft   = randi([0        iWidth-16], 1, 1);
    iRight  = randi([iLeft+16 iWidth],    1, 1);
    iTop    = randi([0        iWidth-16], 1, 1);
    iBottom = randi([iTop+16  iWidth],    1, 1);
    iHpos   = randi([0 iWidth-16], 1, 1);
    iVpos   = randi([0 iWidth-16], 1, 1);
    
    
    %fprintf(fileID, 'pucRefX %d\n', pucRefX);
    %fprintf(fileID, 'pucRefY %d\n', pucRefY);
    %fprintf(fileID, 'pucCurX %d\n', pucCurX);
    %fprintf(fileID, 'pucCurY %d\n', pucCurY);
    fprintf(fileID, 'piMvPos %d\n', piMvPos);
    fprintf(fileID, 'iWidth %d\n', iWidth);
    fprintf(fileID, 'iLeft %d\n', iLeft);
    fprintf(fileID, 'iRight %d\n', iRight);
    fprintf(fileID, 'iTop %d\n', iTop);
    fprintf(fileID, 'iBottom %d\n', iBottom);
    fprintf(fileID, 'iHpos %d\n', iHpos);
    fprintf(fileID, 'iVpos %d\n', iVpos);
    
    fprintf(fileID, '\n');
    
    numbers = randi([0 255], iWidth, iWidth);
    
    formatSpec = 'input_%d_%d %d\n';
    for r=1:length(numbers)
        for c=1:length(numbers)
            fprintf(fileID, formatSpec, (r-1), (c-1), numbers(r,c));
        end
    end
    
    fprintf(fileID, '\n');

    fclose(fileID);
end
