/*
// SAD-based block matching procedure for single macroblock 
// Search area is sepcified by iLeft, iTop, iRight, iBottom. 
// Result is returned through piMvPos. 
// ARG:  pucRef      Reference frame left top pointer. 
//       pucCur      Current   frame left top pointer. 
//       piMvPos     Pointer of position indicated by result MV. 
//       iWidth      Width of the frame. 
//       iLeft       Search area left position. 
//       iRight      Search area right position. 
//       iTop        Search area top position. 
//       iBottom     Search area bottom position. 
//       iHpos       Current block left position in the frame. 
//       iVpos       Current block top position in the frame. 
// Comment: 
//   MV  1 means 1pel 
//   Not check validity of search area. 
iDown = iWidth - 16; 
/* Set start point for Refrence and Search window  
pucCurLeftTop = pucCur + (iVpos * iWidth) + iHpos; 
/* Matching loop 
for(iY = iTop; iY <= iBottom; iY++) { 
/* Set start point for Refrence and Search window 
    pucRefLeft = pucRef + (iY * iWidth); 
    for(iX = iLeft; iX <= iRight; iX++) { 
    /* Init temporal AD 
        iTmpAd = 0; 
        /* Copy Left posision pointer 
        pucC = pucCurLeftTop; 
        pucR = pucRefLeft + iX; 
        /* Get absoluete difference of current position 
        for(iV = 0; iV < 16; iV++) { 
            for(iH = 0; iH < 16; iH++) { 
                iTmpAd += abs((INT32)*(pucC++) - (INT32)*(pucR++)); 
            } 
            /* Current pointer down 1 line 
            pucC += iDown; 
            pucR += iDown; 
        } 
        /* Check minimum AD 
        if(iMinAd > iTmpAd) { 
            iMinAd = iTmpAd; 
            *piMvPos = iX; 
            *(piMvPos+1) = iY;
        } 
    } 
} 
return iMinAd; 
*/


// SAD-based block matching procedure for single macroblock 
// Search area is sepcified by iLeft, iTop, iRight, iBottom. 
// Result is returned through piMvPos.
// mv -> motion vector???
// ARG:  pucRef_y      Reference frame left top pointer. 
//       pucRef_y      Reference frame left top pointer. 
//       pucCur_x      Current   frame left top pointer. 
//       pucCur_y      Current   frame left top pointer. 
//       piMvPos     Pointer of position indicated by result MV. 
//       iWidth      Width of the frame. 
//       iLeft       Search area left position. 
//       iRight      Search area right position. 
//       iTop        Search area top position. 
//       iBottom     Search area bottom position. 
//       iHpos       Current block left position in the frame. 
//       iVpos       Current block top position in the frame. 
// Comment: 
//   MV  1 means 1pel 
//   Not check validity of search area. 
iDown = iWidth - 16; 
/* Set start point for Refrence and Search window */ 
pucCurLeftTop_x = pucCur_x + iHpos;
pucCurLeftTop_y = pucCur_y + iVpos; 
if(pucCurLeftTop_y > iWidth) {
    pucCurLeftTop_x++;
    pucCurLeftTop_y = 0;
}
/* Matching loop */ 
for(iY = iTop; iY <= iBottom; iY++) { 
/* Set start point for Refrence and Search window */
    pucRefLeft_x = pucRef_x; 
    pucRefLeft_y = pucRef_y + iY; 
    if(pucRefLeft_y > iWidth) {
        pucRefLeft_x++;
        pucRefLeft_y = 0;
    }
    for(iX = iLeft; iX <= iRight; iX++) { 
    /* Init temporal AD */ 
        iTmpAd = 0; 
        /* Copy Left posision pointer */ 
        pucC_x = pucCurLeftTop_x;
        pucC_y = pucCurLeftTop_y;

        pucR_x = pucRefLeft_x + iX
        pucR_y = pucRefLeft_y
        /* Get absoluete difference of current position */ 
        for(iV = 0; iV < 16; iV++) { 
            for(iH = 0; iH < 16; iH++) {
                t1 = pucC_x + (pucC_y * iWidth);
                t2 = pucR_x + (pucR_y * iWidth);
                iTmpAd += abs((INT32)*(t1) - (INT32)*(t2)); 
                pucC_y++;
                pucR_y++;
                if(pucC_y > iWidth) {
                    pucC_x++;
                    pucC_y = 0;
                }
                if(pucR_y > iWidth) {
                    pucR_x++;
                    pucR_y = 0;
                }
            } 
            /* Current pointer down 1 line */ 
            pucC_x++;
            pucR_x++; 
        } 
        /* Check minimum AD */ 
        if(iMinAd > iTmpAd) { 
            iMinAd = iTmpAd; 
            *piMvPos = iX; 
            *(piMvPos+1) = iY; 
        } 
    } 
} 
return iMinAd; 

for int i=... 
    for int j = ...
        iTmpAd = 0; 

        for(iV = 0; iV < 16; iV++) { 
            for(iH = 0; iH < 16; iH++) {

                posx i + iV
                posy j + iH
                iTmpAd += abs((INT32)*(input_i_j) - (INT32)*(input_posx_posy)); 
                
            } 
        } 
        /* Check minimum AD */ 
        if(iMinAd > iTmpAd) { 
            iMinAd = iTmpAd; 
            *piMvPos = iX; 
            *(piMvPos+1) = iY; 
        } 