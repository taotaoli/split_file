#include "common_tao.h"
#include "split.h"

int splitFile(char *path, int count, char *savepath, char *savename)
{
    int i = 1, j = 0, c = 0;
    FILE *F = fopen(path, "rb");
    if (F == NULL)
    {
        return -1;
    }
    else
    {
        fseek(F, 0, SEEK_END);      //���ļ�ָ���ƶ����ļ�ĩβ
        int length = ftell(F);      //�����ļ�ָ�뵽�ļ���ͷ���ֽ������������ļ���С
        int yushu = length % count; //����
        int size = length / count;  //ǰ��count-1��ÿһ�ִ�СΪsize�����һ��Ϊsize + yushu
        for (i = 1; i <= count; i++)
        {
            char savefile[100];
            sprintf(savefile, "%s%d.%s", savepath, i, savename);
            //printf("%s", savefile);
            LOGI(" process [%d/%d] [ %s ]", i,count, savefile);
            FILE *P = fopen(savefile, "wb");
            if (P == NULL)
            {
                fclose(F);
                return -1;
            }
            else
            {
                fseek(F, (i - 1) * size, SEEK_SET);
                if (i == count)
                {
                    for (j = 0; j <= size + yushu; j++)
                    {
                        c = fgetc(F);
                        fputc(c, P);
                    }
                }
                else
                {
                    for (j = 0; j < size; j++)
                    {
                        c = fgetc(F);
                        fputc(c, P);
                    }
                }
            }
            fclose(P);
        }
        fclose(F);
        return 0;
    }
}
