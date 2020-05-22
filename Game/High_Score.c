#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int ind, sorted=0, is_high=0;

typedef struct
{
    int score;
    char name[50];
}High_Score;

High_Score hg_score[6];

void high_score_read()
{
    FILE *fp=fopen("score.txt", "r");
    FILE *fp2=fopen("name.txt", "r");
    ind=0;

    while(fscanf(fp, "%d", &hg_score[ind].score)!=EOF)
    {
        ind++;
    }

    for(int i=0;i<ind;i++)
    {
        fgets(hg_score[i].name, 50, fp2);
    }

    fclose(fp);
    fclose(fp2);

}

void high_score_write()
{
    FILE *out=fopen("score.txt", "w");
    FILE *out2=fopen("name.txt", "w");

    for(int i=0; i<ind; i++)
    {
        fprintf(out, "%d\n",hg_score[i].score);
    }

    for(int i=0; i<ind; i++)
    {
        fprintf(out2, "%s",hg_score[i].name);
    }

    fclose(out);
    fclose(out2);
}

int cmp(const void *a,  const void *b)
{
    High_Score ta=*((High_Score *)a);
    High_Score tb=*((High_Score *)b);

    if(ta.score < tb.score)
        return 1;
    else if(ta.score>tb.score)
        return -1;

    else return 0;
}

void sort_high_score()
{
    High_Score temp, temp2;
    for(int i=0;i<5;i++)
    {
        if(!is_high && hg_score[5].score>hg_score[i].score)
        {
            is_high=1;
            temp=hg_score[i];
            hg_score[i]=hg_score[5];
            i++;
        }

        if(is_high)
        {
            temp2=hg_score[i];
            hg_score[i]=temp;
            temp=temp2;
        }
    }

}

int main()
{
    int score=180;
    char name[50]="Tahrima Islam Rimi\n";

    hg_score[5].score=score;
    strcpy(hg_score[5].name, name);

//    printf("%d\n",hg_score[5].score);
//    printf("%s",hg_score[5].name);

    high_score_read();
    sort_high_score();

    if(is_high)
    {
        high_score_write();
        is_high=0;
    }

    for(int i=0;i<ind;i++)
    {
        printf("%s",hg_score[i].name);
        printf("%d\n",hg_score[i].score);
    }

    return 0;
}
