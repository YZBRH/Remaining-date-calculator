#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int compare_min(int a, int b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}//求两数较小值

int compare_max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}//求两数较大值

int leap_year_number(year1, year2)
{
	if (year1 == year2)
	{
		return 0;
	}
	int i = year1 + 1;
	int leap_year = 0;
	for (; i < year2; i++)
	{
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
		{
			leap_year++;
		}
	}
	return leap_year;
}//判断两年份之间有几个闰年



int main()
{
	int year1 = 0;
	int month1 = 0;
	int day1 = 0;
	int year2 = 0;
	int month2 = 0;
	int day2 = 0;

	int a = 0;
begin:
		while (1)
		{
			printf("输入1以自动获取系统时间为起始日期，输入其他数字以自定义起始时间:>>");
			scanf("%d", &a);
			if (a == 1)
			{
				time_t timep;
				struct tm* p;
				time(&timep);
				p = localtime(&timep);
				year1 = 1900 + p->tm_year;
				month1 = 1 + p->tm_mon;
				day1 = p->tm_mday;
				printf("获取成功，当前时间为%04d-%02d-%02d\n", year1, month1, day1);
			}//自动获取系统时间
			else
			{
				printf("请输入起始年月日（使用空格分开）:>>");
				scanf("%d %d %d", &year1, &month1, &day1);
			}
				printf("请输入终止年月日（使用空格分开）:>>");
				scanf("%d %d %d", &year2, &month2, &day2);//收集输入数据

			int year_test = compare_min(year1, year2);
			int month_test_min = compare_min(month1, month2);
			int month_test_max = compare_max(month1, month2);
			int day_test_min = compare_min(day1, day2);
			int day_test_max = compare_max(day1, day2);
			if (year_test < 0 || month_test_min < 1 || month_test_max>12 || day_test_min < 1 || day_test_max>32)
			{
				printf("无效输入，请重试\n");
				continue;
			}//第一次排除不合理数据
			break;
		}//数据输入及判断部分

	int year_gap = year2 - year1;
	if (year_gap < 0)
	{
		goto begin;
	}//第二次排除不合理数据（年份之差为负值）
	int leap_year = leap_year_number(year1, year2);//判断两数据之间有几个闰年
	//printf("有%d个闰年\n", leap_year);
	int sum = 0;
	if (year1 != year2)
	{
		sum = (year2 - year1 - 1) * 365 + leap_year;
	}//第一部分（主要年份的计算）
	
	int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year1 == year2)
	{
		for (int i = month1 + 1; i < month2; i++)
		{
			sum += arr[i];//计算month1到month2之间月份天数之和
		}
		if (((year1 % 4 == 0 && year1 % 100 != 0) || year1 % 400 == 0) && month1 <= 2 && month2 > 2)
		{
			sum += 1;//若是闰年且中间月份包括了2月，则补上闰年的这一天
		}

	}//同一年时
	else
	{
		for (int i = month1 + 1; i <= 12; i++)
		{
			sum += arr[i];//从month1+1到年底的天数
		}
		for (int i = 1; i < month2; i++)
		{
			sum += arr[i];//从年初到month2-1的天数
		}
		if (((year1 % 4 == 0 && year1 % 100 != 0) || year1 % 400 == 0) && month1 <= 2)
		{
			sum += 1;//year1是闰年且month1小于等于2就补上闰年的一天
		}
		if (((year2 % 4 == 0 && year2 % 100 != 0) || year2 % 400 == 0) && month2 > 2)
		{
			sum += 1;//year2是闰年且month2大于2就补上闰年的一天
		}
	}//非同一年时
	//第二部分（主要月份计算）
	if (month1 == month2 && year1 == year2)
	{
		sum += day2 - day1;
	}//同一月时
	else
	{
		sum += arr[month1] - day1 + day2;//month1到月底的天数+月初到month2的天数
	}//非同一月时
	//第三部分（主要天数计算）

	printf("从%04d-%02d-%02d至%04d-%02d-%02d共有%d天", year1, month1, day1, year2, month2, day2, sum);

	return 0;
}