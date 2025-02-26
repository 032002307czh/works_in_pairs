#include "inclu.h"
#include "data.h"
void List()
{ //表单
    int temp[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, t, t1, j, bd = 0, k;

    for (int i = 0; i < con; i++)
    { //给5-8人设置缺勤情况
        t = rand() % 90;
        for (j = 0; j < 8; j++)
        {
            if (t == temp[j] || s[t].credit > 2.5)
            {
                i--;
                break;
            }
        }
        if (j == 8)
        {
            temp[bd] = t;
            bd++;
            for (k = 0; k < 16; k++)
            {
                t1 = rand() % 20;
                if (s[t].a[t1] == 1)
                {
                    s[t].a[t1] = 0;
                }
                else
                {
                    k--;
                }
            }
        }
    }
    for (int i = 0; i < 20; i++)
    { // 0-3
        bd = con;
        for (j = con; j < 11; j++)
        {
            temp[con] = -1;
        }
        t = rand() % 4;
        for (k = 0; k < t; k++)
        {
            t1 = rand() % 90;
            for (j = 0; j < con + t; j++)
            {
                if (t1 == temp[k])
                {
                    k--;
                    break;
                }
            }
            if (j == con + t)
            {
                temp[bd] = t1;
                bd++;
                s[t1].a[i] = 0;
            }
        }
    }
    FILE *fp;
    if (course == 0)
        fp = fopen("c:\\科目1.txt", "w"); //打开文件以便写入数据
    if (course == 1)
        fp = fopen("c:\\科目2.txt", "w"); //打开文件以便写入数据
    if (course == 2)
        fp = fopen("c:\\科目3.txt", "w"); //打开文件以便写入数据
    if (course == 3)
        fp = fopen("c:\\科目4.txt", "w"); //打开文件以便写入数据
    if (course == 4)
        fp = fopen("c:\\科目5.txt", "w"); //打开文件以便写入数据
    for (int i = 0; i < 90; i++)
    {
        for (j = 0; j < 20; j++)
        {
            //将a数组中的整数写入fp指向的c:\a.txt文件
            if (j == 0)
            {
                fprintf(fp, "学生_%2d 绩点_%.2f ", i, s[i].credit);
            }
            fprintf(fp, "%d ", s[i].a[j]);
            if (j == 19)
                fprintf(fp, "\n");
        }
    }
    fclose(fp); //写入完毕，关闭文件
}

//初始化
void Init()
{
    for (int i = 0; i < 90; i++)
    {
        s[i].count = 0;
        s[i].flag = 0;
        for (int j = 0; j < 20; j++)
        {
            s[i].a[j] = 1;
        }
    }
}

//计算e值
double calculateE()
{
    double e = (total_number * 1.0) / total_count;
    return e;
}

//如果 class_count-s.count==5,则不是80%缺勤的人
void Deal()
{
    for (int i = 0; i < 90; i++)
    {
        if (class_count - s[i].count == 5)
        {
            s[i].flag = 1;
        }
    }
}

//更新80%缺勤名单
void Update()
{
    int j = 0;
    for (int i = 0; i < 90; i++)
    {
        if (s[i].flag == 0)
        {
            as[j] = s[i];
            j++;
        }
    }
    absent_count = j;
}

int main()
{
    int j = 0, sign = 0, temp; //记录迟到队列
    srand(time(0));            //放在主函数
    for (int i = 0; i < 90; i++)
    {
        j = rand() % 30;
        s[i].credit = 0.1 * j + 1; //绩点
    }
    for (course = 0; course < 5; course++)
    {                           // 5次课循环五次
        Init();                 //初始化90个结构体
        int later[90], cnt = 0; //
        for (int i = 0; i < 90; i++)
            later[i] = -2;
        con = rand() % 4 + 5;
        List(); //表单
        for (class_count = 0; class_count < 20; class_count++)
        {                         //点20次名
            if (class_count == 0) //点一次
            {
                for (j = 0; j < 90; j++)
                {
                    if (s[j].credit > 2.5)
                        continue; //放弃绩点高于2.5的
                    else
                    {
                        temp = cnt;
                        sign = 0;
                        total_count++;
                        if (s[j].a[class_count] == 0)
                        {
                            total_number++;
                            later[cnt] = j;
                            cnt++;

                            s[j].count++; //点到几次
                        }
                    }
                }
            }

            else
            {
                temp = cnt;
                for (int i = 0; i < temp; i++) //点名单里的
                {
                    if (later[i] < 0)
                        continue;
                    total_count++;
                    if (s[later[i]].a[class_count] == 0)
                    {
                        s[later[i]].count++; //点到几次
                        total_number++;
                    }
                    else
                    {
                        if (class_count > s[later[i]].count + 4) //淘汰掉那些迟到不够的
                            later[i] = -1;
                    }
                }
            }
        }
    }
    cout << "##" << total_count << " " << total_number << endl;
    cout << calculateE();
    return 0;
}
