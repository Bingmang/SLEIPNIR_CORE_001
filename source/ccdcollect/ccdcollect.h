#ifndef __CCDCOLLECT_H__
#define __CCDCOLLECT_H__
/******************************************************************************/
#define GRAPH_WIDTH 128

/******************************************************************************/
//struct
typedef struct ccd_data
{
    int id;
    uint8 graph[GRAPH_WIDTH];    //CCDÍ¼Ïñ
}CCD_data,*pCCD_data;

/******************************************************************************/
//extern
extern CCD_data ccd0;
extern CCD_data ccd1;
//extern CCD_data ccd2;

/******************************************************************************/
//function
extern void CCD_Collect(CCD_data *ccd);
extern void CCD_Init(void);

/******************************************************************************/
#endif
