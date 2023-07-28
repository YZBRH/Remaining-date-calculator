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
}//��������Сֵ

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
}//�������ϴ�ֵ

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
}//�ж������֮���м�������



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
			printf("����1���Զ���ȡϵͳʱ��Ϊ��ʼ���ڣ����������������Զ�����ʼʱ��:>>");
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
				printf("��ȡ�ɹ�����ǰʱ��Ϊ%04d-%02d-%02d\n", year1, month1, day1);
			}//�Զ���ȡϵͳʱ��
			else
			{
				printf("��������ʼ�����գ�ʹ�ÿո�ֿ���:>>");
				scanf("%d %d %d", &year1, &month1, &day1);
			}
				printf("��������ֹ�����գ�ʹ�ÿո�ֿ���:>>");
				scanf("%d %d %d", &year2, &month2, &day2);//�ռ���������

			int year_test = compare_min(year1, year2);
			int month_test_min = compare_min(month1, month2);
			int month_test_max = compare_max(month1, month2);
			int day_test_min = compare_min(day1, day2);
			int day_test_max = compare_max(day1, day2);
			if (year_test < 0 || month_test_min < 1 || month_test_max>12 || day_test_min < 1 || day_test_max>32)
			{
				printf("��Ч���룬������\n");
				continue;
			}//��һ���ų�����������
			break;
		}//�������뼰�жϲ���

	int year_gap = year2 - year1;
	if (year_gap < 0)
	{
		goto begin;
	}//�ڶ����ų����������ݣ����֮��Ϊ��ֵ��
	int leap_year = leap_year_number(year1, year2);//�ж�������֮���м�������
	//printf("��%d������\n", leap_year);
	int sum = 0;
	if (year1 != year2)
	{
		sum = (year2 - year1 - 1) * 365 + leap_year;
	}//��һ���֣���Ҫ��ݵļ��㣩
	
	int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year1 == year2)
	{
		for (int i = month1 + 1; i < month2; i++)
		{
			sum += arr[i];//����month1��month2֮���·�����֮��
		}
		if (((year1 % 4 == 0 && year1 % 100 != 0) || year1 % 400 == 0) && month1 <= 2 && month2 > 2)
		{
			sum += 1;//�����������м��·ݰ�����2�£������������һ��
		}

	}//ͬһ��ʱ
	else
	{
		for (int i = month1 + 1; i <= 12; i++)
		{
			sum += arr[i];//��month1+1����׵�����
		}
		for (int i = 1; i < month2; i++)
		{
			sum += arr[i];//�������month2-1������
		}
		if (((year1 % 4 == 0 && year1 % 100 != 0) || year1 % 400 == 0) && month1 <= 2)
		{
			sum += 1;//year1��������month1С�ڵ���2�Ͳ��������һ��
		}
		if (((year2 % 4 == 0 && year2 % 100 != 0) || year2 % 400 == 0) && month2 > 2)
		{
			sum += 1;//year2��������month2����2�Ͳ��������һ��
		}
	}//��ͬһ��ʱ
	//�ڶ����֣���Ҫ�·ݼ��㣩
	if (month1 == month2 && year1 == year2)
	{
		sum += day2 - day1;
	}//ͬһ��ʱ
	else
	{
		sum += arr[month1] - day1 + day2;//month1���µ׵�����+�³���month2������
	}//��ͬһ��ʱ
	//�������֣���Ҫ�������㣩

	printf("��%04d-%02d-%02d��%04d-%02d-%02d����%d��", year1, month1, day1, year2, month2, day2, sum);

	return 0;
}