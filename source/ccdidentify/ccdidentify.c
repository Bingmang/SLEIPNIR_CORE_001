
#include "common.h"
#include "ccdidentify.h"

/***********************************************************/
#define g_noisevalue 255
#define shield_point 15     //两侧的屏蔽

/***********************************************************/
//曝光时间
int exposure_time = 5;  //曝光时间，默认5ms曝光一次
//CCD变量
uint8 g_ccd_middle = 64;  //58
int threshold = 50;
//图像识别参数
uint8 left_toggle_point;
uint8 right_toggle_point;
signed int g_angerror_temp = 0;
signed int last_g_angerror_temp = 0;
uint8 middle_temp = 63;
uint8 g_leftbreak_num = 0;
uint8 g_rightbreak_num = 0;
uint8 g_endleftbreak_num = 0;
uint8 g_endrightbreak_num = 0;
uint8 g_endmiddlebreak_num = 0;
uint8 ccdleftsum = 0;
uint8 ccdrightsum = 0;
uint8 leftn = 0;
uint8 rightn = 0;
int g_test = 0;
/******************************************************************************/
//CCD图像识别
uint8 CCD_Identify(CCD_data *ccd)
{
    int k;

    //去单个噪点
    for(k = shield_point; k < GRAPH_WIDTH - shield_point - 1; k++)
    {
        if(ABS(ccd->graph[k] - ccd->graph[k-1]) > g_noisevalue
         &&ABS(ccd->graph[k] - ccd->graph[k+1]) > g_noisevalue)
        {
            ccd->graph[k] = (ccd->graph[k-1] + ccd->graph[k+1]) / 2;
        }
    }

	//第一种判别图像的方法（变化率方法找跳变沿）

	for (k = 63; k > shield_point; k--) //63
	{
		if ((ccd->graph[k] - ccd->graph[k - 3]) >= threshold)
		{
			g_leftbreak_num = 0;
			break;
		}
		else g_leftbreak_num++;
	}

	left_toggle_point = k - 1;

	for (k = 64; k < GRAPH_WIDTH - 1 - shield_point; k++)
	{
		if ((ccd->graph[k] - ccd->graph[k + 3]) >= threshold)
		{
			g_rightbreak_num = 0;
			break;
		}
		else g_rightbreak_num++;
	}

	right_toggle_point = k + 1;

	//如果有一边检测不到跳变沿，则用另一边的跳变沿估算中点
	if (g_leftbreak_num > 50)
		middle_temp = right_toggle_point / 2;
	else if (g_rightbreak_num > 50)
		middle_temp = left_toggle_point / 2;
	else
		middle_temp = (left_toggle_point + right_toggle_point) / 2;




	//如果游戏开始，判定终点停车
	if (g_gameBegin == 1)
	{
		for (k = 39; k < 55; k++)
		{
			if (ccd->graph[k] < 100)
				g_endleftbreak_num++;
		}
		for (k = 55; k < 70; k++)
		{
			if (ccd->graph[k] > 100)
				g_endmiddlebreak_num++;
		}
		for (k = 70; k < 89; k++)
		{
			if (ccd->graph[k] < 100)
				g_endrightbreak_num++;
		}
	}



    return middle_temp;
}
