#include<iostream>
#include<math.h>
#include<conio.h>
#include<windows.h>

using namespace std;

void fontSize(int size)
{
	//FONT SIZE CHANGE 
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;                   // Width of each character in the font
		cfi.dwFontSize.Y = size;                  // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


int leapYear ( int input )
//returns TRUE or 1 in case of leap year as input 
{
	if((input%4 == 0 && input%100 != 0) || (input%400 == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

long double simpleInterest ( double pAmount , double aRate , double time )
//rate in percent 
//rate should be acc to years , time should be in years 
{
	long double result = 0;
	
	result = pAmount * ( 1 + ( ( aRate / 100 ) * time) );
	
	return result;
}

long double compoundInterest ( double pAmount , double aRate , double time , double compoundingFrequency )
//rate should be acc to years , time should be in years
//rate in percent  
//if the compounding effect occurs ones per month then compounding frequency will be 12
{
	long double result = 0;
	
	result = pAmount * pow( ( 1 + ( ( aRate / 100 ) / compoundingFrequency ) ) , ( compoundingFrequency * time ) );
	
	return result;
}

long double stringTOnumber ( string input )
//returns 0 in case of error 
{
	int stringLength = input.size();
	int temp[stringLength+10];
	int yesDEC = 0 , decStart = 0;
	
	for(int i=0 ; i<stringLength ; i++)
	{
		//generating digits array for the integer part 
		switch(input[i])
		{
			case '0' : temp[i] = 0; decStart = i; break; 
			case '1' : temp[i] = 1; decStart = i; break;
			case '2' : temp[i] = 2; decStart = i; break;
			case '3' : temp[i] = 3; decStart = i; break;
			case '4' : temp[i] = 4; decStart = i; break;
			case '5' : temp[i] = 5; decStart = i; break;
			case '6' : temp[i] = 6; decStart = i; break;
			case '7' : temp[i] = 7; decStart = i; break;
			case '8' : temp[i] = 8; decStart = i; break;
			case '9' : temp[i] = 9; decStart = i; break;
			case '.' : yesDEC++; 	break;
			default : return 0;
 		}
 		if(yesDEC!=0)
 		{
 			break;
		}
	}
	
	long double sum = 0;
	int tempCounter = decStart;
	
	//summing the integer part
	for(int i=0 ; i<=decStart ;i++)
	{
		sum = sum + (temp[i] * pow(10,tempCounter));
		tempCounter--;
	}
	
	
	//checking if their is decimal part to save computational time and power 
	if(yesDEC!=0)
 	{
 		//generating digits array for decimal part
 		int tempDEC[stringLength+10];
 		long double sumDEC = 0; 
 		tempCounter = 0;
 		int tempCounter0 = 0;
 		
 		for(int i=decStart+2 ; i<stringLength ;i++)
 		{
 			switch(input[i])
		{
			case '0' : tempDEC[i] = 0; break; 
			case '1' : tempDEC[i] = 1; break;
			case '2' : tempDEC[i] = 2; break;
			case '3' : tempDEC[i] = 3; break;
			case '4' : tempDEC[i] = 4; break;
			case '5' : tempDEC[i] = 5; break;
			case '6' : tempDEC[i] = 6; break;
			case '7' : tempDEC[i] = 7; break;
			case '8' : tempDEC[i] = 8; break;
			case '9' : tempDEC[i] = 9; break;
			case '.' : return 0; break;
			default : return 0;
 		}
 		tempCounter++;
		}
		
		//summing the decimal part 
		tempCounter0 = tempCounter; 
		for(int i=decStart+2 ; i<stringLength ;i++)
 		{
 			sumDEC = sumDEC + (tempDEC[i] * pow(10,tempCounter-1));
 			tempCounter--;
 		}
 		//converting and adding the sum of decimal part to integer part , here { / pow() } is used to convert integer sum to decimal value 
 		sum = sum + ( sumDEC / pow(10,tempCounter0) ) ;
	}
	return sum;
}



//counts the number of days till DD/MM/YYYY 
long int daysCounter( int date0 , int month0 , int year0 )
//returns 0 in case of error
{
	long int days = 0;
	
	//checking of errors in input's
	if(date0>31)
	{
		return 0;
	}
	if(month0>12)
	{
		return 0;
	}
	
	//counting days till this year 
	for(int i=0;i<year0;i++)
	{
		days = days + 365 + leapYear(i) ;
	}
	
	//counting days till this month 
	
	for(int i=1;i<=month0;i++)
	{
		if(i==2)
		{
			if(leapYear(year0))
			{
				days = days + 29;
			}
			else
			{
				days = days + 28;
			}
			
		}
		else
		if(i<=7)
		{
			if(i%2 == 0)
			{
				days = days + 30;
			}
			else
			{
				days = days + 31;
			}
		}
		else
		{
			if(i%2 != 0)
			{
				days = days + 30;
			}
			else
			{
				days = days + 31;
			}
		}
	}
	
	days = days + date0;
	
	return days;
} 



int main()
{
	fontSize(24);
	begin : ;	//goto statement 
	system("cls");
	//all varaible that will be needed
	int date0 , date1 , month0 , month1 , year0 , year1;
	string inputDate0 , inputDate1;
	double principleAmount = 0 , time = 0 , rate = 0 , frequency = 0 ;
	long double finalAmount  = 0;
	int choice = 0;
	
	//asking for choice to calc SI or CI
	cout<<"Select mode - \n\n";
	cout<<"1. simple interest\n";
	cout<<"2. compound interest\n\n";
	cout<<"Enter your choice - ";
	cin>>choice;
	
	//checking for wrong input 
	if(choice!=1 && choice!=2)
	{
		cout<<choice;
		goto begin;
	}
	
	system("cls");
	
	//asking for the common parameters 
	cout<<"Enter the principle amount - ";
	cin>>principleAmount;
	cout<<"\nMultiply the interest rate by 12 if its per month\nEnter the interest rate per annum in % - ";
	cin>>rate;
	
	//asking for teh frequency 
	if(choice==2)
	{
		cout<<"\nIf the compounding effect takes place ones per month in a year then compounding frequency will be 12";
		cout<<"\nEnter the compounding frequency - ";
		cin>>frequency;
	}
	
	system("cls");
	
	cout<<"Enter the starting date in format [ DD/MM/YYY ] - ";
	cin>>inputDate0;
	
	system("cls");
	
	cout<<"Enter the ending date in format [ DD/MM/YYYY ] - ";
	cin>>inputDate1;
	
	//converting date string to individual strings so that it can be converted to number 
	
	string dat0 = "", dat1  = "", mont0  = "", mont1  = "", yea0  = "", yea1  = "";
	
	dat0 = dat0 + inputDate0[0];
	dat0 = dat0 + inputDate0[1];
	dat1 = dat1 + inputDate1[0]; 
	dat1 = dat1 + inputDate1[1];
	
	
	mont0 = mont0 + inputDate0[3]; 
	mont0 = mont0 + inputDate0[4];
	mont1 = mont1 + inputDate1[3];
	mont1 = mont1 + inputDate1[4];
	
	yea0 = yea0 + inputDate0[6];
	yea0 = yea0 + inputDate0[7];
	yea0 = yea0 + inputDate0[8];
	yea0 = yea0 + inputDate0[9];
	yea1 = yea1 + inputDate1[6];
	yea1 = yea1 + inputDate1[7];
	yea1 = yea1 + inputDate1[8];
	yea1 = yea1 + inputDate1[9];
	
	
	//converting strings to numbers
	
	date0 = stringTOnumber(dat0);
	date1 = stringTOnumber(dat1);
	
	month0 = stringTOnumber(mont0);
	month1 = stringTOnumber(mont1);
	
	year0 = stringTOnumber(yea0);
	year1 = stringTOnumber(yea1);
	
	
	//calculating time 
	time = (daysCounter(date1 , month1 , year1) - daysCounter(date0 , month0 , year0)) / 365;
	
	//calculating and displaying output
	system("cls");
	if(choice==1)
	{
		cout<<"Total amount after applying simple interest "<<rate<<" for "<<time<<" years is ";
		finalAmount = simpleInterest(principleAmount , rate , time);
		cout<<finalAmount;
	}
	else
	{
		cout<<"Total amount after applying compound interest is "<<rate<<" for "<<time<<" years with compounding frequency "<<frequency<<" is ";
		finalAmount = compoundInterest(principleAmount , rate , time , frequency);
		cout<<finalAmount;
	}
	cout<<endl<<endl;
	system("pause");
	return 0;
}
