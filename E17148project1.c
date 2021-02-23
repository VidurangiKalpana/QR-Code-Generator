#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void positionSquare(int type); //Postion square function prototype
void charSquare(int ch,int type); //Character square function prototype
void shortQR(unsigned char shortHash[],int length,int type); //Sort QR code function prototype
void longQR(unsigned char longHash[],int length,int type); //long QR code function prototype
int upperCase(char*string); //upperCase function prototype

//Test Driver
int main(int argc,char*argv[]){

	//Argument Handling

	int type; //Type of arguments	

	if(argc==1){ //If count of arguments is one
		type=40; //If no second argument is given,print QR code in black
	}else if(argc==2){ //If count of arguments is two
		if(strcmp("-h",argv[1])==0){
			type=1; //If the second argument is "-h", Request for help by giving usages of program
		}else{
			type=2; //If the second argument is not "-h", it is incorrect usage of arguments
		}
	}else if(argc==3){ //If count of arguments is three
		if(strcmp("-c",argv[1])==0){
			upperCase(argv[2]); //If there are lower case characters in third argument,convert them in to upper case
			
			if(strcmp(argv[2],"BLACK")==0){ //Checking that third argument is black
				type=40; 
			}else if(strcmp(argv[2],"RED")==0){ //Checking that third argument is red
				type=41;
			}else if(strcmp(argv[2],"GREEN")==0){ //checking that third argument is green
				type=42;
			}else if(strcmp(argv[2],"YELLOW")==0){ //checking that third argument is yellow
				type=43;
			}else if(strcmp(argv[2],"BLUE")==0){ //checking that third argument is blue
				type=44;
			}else if(strcmp(argv[2],"MAGENTA")==0){ //checking that third argument is magenta
				type=45;
			}else if(strcmp(argv[2],"CYAN")==0){ //checking that third argument is cyan
				type=46;
			}else{
				type=3; //If the third argument is not one of any given colors, it is invalid argument for color
			}
		}else if(strcmp("-h",argv[1])==0){
			type=2; //If the second argument is '-h', it is incorrect usage of arguments
		}else{
			type=2; //If the second argument is not '-c' or '-h', it is incorrect usage of arguments
		}
	}else{
		type=2; //If there are more than 3 arguments, it is incorrect usage of arguments

	}
	
	if(type==2){
		printf("Incorrect usage of arguments.\n"); //Print as Incorrect usage of arguments.
	}else if(type==3){
		printf("Invalid argument for color.\n"); //Print as Invalid argument for color.
	}

	//If it is incorrect usage of arguments,invalid argument for color or Request for help, print the followings
	if((type>=1) && (type<=3)){
		printf("usage :\n");
		printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
		printf("%s -h for the help about the program\n",argv[0]);
		return -1;
	}else{


		//Varible Declarations
		unsigned char URL[125]; //Declarartion of URL array with the size of 125
		unsigned char shortHash[24]; //Declaration of short hashed array with the size of 24
		unsigned char longHash[132]; //Declaration of long hashed array with the size of 132
		unsigned char shortHashFinal[24]; //Declaration of final short hashed array
		unsigned char longHashFinal[132]; //Declaration of final long hashed array
		int x,y,X,Y,i,j,k;
		int index=0,a;

		//User enters the URL
		printf("Enter the URL: ");
		scanf("%s",URL);
		//printf("\n"); //Get a new line after user input

		unsigned char reverse[24-(strlen(URL)+1)]; //Declarartion of reverse array of short hashed string
		unsigned char Reverse[132-(strlen(URL)+1)]; //Declarartion of reverse array of lon hashed array


		x=(23)/strlen(URL); //Get number of loops of printing URL in the short hashed string
		y=(23)%strlen(URL); //Get number of characters which are to be filled after printing loops of URL in short hashed string

		X=(131)/strlen(URL); //Get number of loops of printing URL in the long hashed string
                Y=(131)%strlen(URL); //Get number of characters which are to be filled after printing loops of URL in long hashed string
	
		

		//Check if length of URL is greater than 3 and less than 120 
		if((strlen(URL))>3 && (strlen(URL))<120){
			
			//clear terminal after getting the URL
	                {
        	        system("tput clear");
               		}
	
			//Hash the string to a fixed length string

			if((strlen(URL))<=20){ //Check if length of URL is greater than or equal to 20

				shortHash[0]=((strlen(URL))+50); //First character of short hashed string 
				
				//Put URL characters as next characters in the short hashed string after the first character
				for(i=1;i<(strlen(URL)+1);i++){
					shortHash[i]=URL[i-1];
				}

				//Get short hashed string without the reversed part
				for(i=1;i<x;i++){ //loop to get set of characters one by one
					for(j=1+(strlen(URL)*i);j<=(strlen(URL)+(strlen(URL)*i));j++){ //loop to go through URL characters
						//Add i to ASCII value of URL characters and append them to short hashed array
						shortHash[j]=URL[index]+i;
						index++; //Increment index value
					}
					index=0; //Reset index to 0 value
				}
				
				//Fill the remained spaces of short hashed string
				for(i=0;i<y;i++){
					//Add x to ASCII value of URL characters and append them from first free index to last one
					shortHash[(1+(x*strlen(URL)))+i]=URL[i]+x;

				}
				
				/*
					Without reversing part the short hashed string is now complete
					Then get the reversed part of short hashed array
						=>When the length of reverse array is an even number
						=>When the length of reverse array is an odd number

				*/
				//Get the length of reversed array
				a=24-(1+strlen(URL));
				//Set index value to the last index value of short hashed array
				index=23;
				
				//Loop to fiil the half of reversed array by short hashed array elements
				for(i=0;i<(a/2);i++){
					reverse[i]=shortHash[index];
					index--; //Decrement of index value
				}
				
				//If length of reverse array is an even number
				if((a)%2==0){

					//Reset index value
					index=strlen(URL)+(a/2);
					
					//Fill other half of reverse array
                                        for(j=i;j<=a;j++){
                                                reverse[j]=shortHash[index];
                                                index--; //Decrement of index
                                        }
				
				//If length of reverse array is an odd number
				}else{
					//Reset index value
					index=strlen(URL)+(a/2);
					//Append next character of short hashed array to next index that is to be filled in reverse array
                                        reverse[i]=shortHash[index+1];

					//Then fill other half of reverse array
                                        for(j=i+1;j<=a;j++){
                                                reverse[j]=shortHash[index];
                                                index--; //Decrement of index
                                        }

				}
				
				//Reset index value
				index=0;
				
				//Append reverse array to short hashed array
				for(i=strlen(URL)+1;i<=23;i++){				
					shortHash[i]=reverse[index];
					index++; //Increment of index
				}

				//Remove garbage values that will add to shortHash array
				for(i=0;i<24;i++){
					shortHashFinal[i]=shortHash[i];
				}

				shortQR(shortHashFinal,24,type);

			}else{
				index=0;
				longHash[0]=((strlen(URL))+50); //First character of long hashed string 

                                //Put URL characters as next characters in the long hashed string after the first character
                                for(i=1;i<(strlen(URL)+1);i++){
                                        longHash[i]=URL[i-1];
                                }

                                //Get long hashed string without the reversed part
                                for(i=1;i<X;i++){ //loop to get set of characters one by one
                                        for(j=1+(strlen(URL)*i);j<=(strlen(URL)+(strlen(URL)*i));j++){ //loop to go through URL characters
                                                //Add i to ASCII value of URL characters and append them to long hashed array
                                                longHash[j]=URL[index]+i;
                                                index++; //Increment index value
                                        }
                                        index=0; //Reset index to 0 value
                                }

                                //Fill the remained spaces of long hashed string
                                for(i=0;i<Y;i++){
                                        //Add X to ASCII value of URL characters and append them from first free index to last one
                                        longHash[(1+(X*strlen(URL)))+i]=URL[i]+X;

                                }

                                /*
                                        Without reversing part the long hashed string is now complete
                                        Then get the reversed part of long hashed array
                                                =>When the length of Reverse array is an even number
                                                =>When the length of Reverse array is an odd number

                                */
				//Get the length of reversed array
				a=132-(1+strlen(URL));
				//Set index value to the last index value of long hashed array
                                index=131;

                                //Loop to fiil the half of reversed array by long hashed array elements
                                for(i=0;i<(a/2);i++){
                                        Reverse[i]=longHash[index];
                                        index--; //Decrement of index value
                                }

                                //If length of Reverse array is an even number
                                if(a%2==0){

                                        //Reset index value
                                        index=strlen(URL)+(a/2);

                                        //Fill other half of Reverse array
                                        for(j=i;j<=a;j++){
                                                Reverse[j]=longHash[index];
                                                index--; //Decrement of index
                                        }

                                //If length of Reverse array is an odd number
                                }else{
                                        //Reset index value
                                        index=strlen(URL)+(a/2);
                                        //Append next character of long hashed array to next index that is to be filled in Reverse array
                                        Reverse[i]=longHash[index+1];

                                        //Then fill other half of Reverse array
                                        for(j=i+1;j<=a;j++){
                                                Reverse[j]=longHash[index];
                                                index--; //Decrement of index
                                        }
				}

                                //Reset index value
                                index=0;

                                //Append Reverse array to long hashed array
                                for(i=strlen(URL)+1;i<=131;i++){
                                        longHash[i]=Reverse[index];
                                        index++; //Increment of index
                                }

                                //Remove garbage values that will add to longHash array
                                for(i=0;i<132;i++){
                                        longHashFinal[i]=longHash[i];
                                }

				longQR(longHashFinal,132,type);
			}
		
		}else if((strlen(URL))<=3){ //If the length of URL is less than or equal to 3
			printf("String is too short. Not supported by available QR versions");
		}else{ //If the length of URL is greater than or equal to 120
			printf("String is too long. Not supported by available QR versions:");
		}
		printf("\n");
	}
	return 0;
}

//upperCase function definition to convert the lower case characters to upper case characters

int upperCase(char*string){
	int i,j;
	for(int i=0;string[i]!='\0';i++){
		if(string[i]>=97 && string[i]<=122){ //If string[i] is a lower case character
			string[i]=string[i]-('a'-'A'); //Sustract 32 from lower case character
		}
	}
	return 1; //Return integer value
}


//position square with different colours
void positionSquare(int type){
	int i,j;
	//outer square
	for(i=1;i<=6;i++){
		for(j=1;j<=6;j++){
			printf("\x1B[%dm  ",type); //Two spaces for 1 small sq
			printf("\x1B[0m"); // Reset code
		}
		printf("\x1B[1B"); //cursor moves down 1 time
		printf("\x1B[12D"); //cursor moves left 12 times
	}
	
	//Set cursor to the start of next inner square
	printf("\x1B[5A"); // cursor moves up 5 times
	printf("\x1B[2C"); //cursor moves right 2 times 
	
	//Next inner square
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			printf("\x1B[47m  "); //two spaces for 1 small sq
			printf("\x1B[0m"); //Reset code
		}
		printf("\x1B[1B"); //cursor moves down 1 time
		printf("\x1B[8D"); //cursor moves left 8 times
	}
	//set cursor to the start of next inner square
	printf("\x1B[3A"); //cursor moves up 3 times
	printf("\x1B[2C"); //cursor moves right two times
	
	//Next inner square
	for(i=1;i<=2;i++){
		for(j=1;j<=2;j++){
			printf("\x1B[%dm  ",type); //two spaces for 1 sq
			printf("\x1B[0m"); //Reset code
		}
		printf("\x1B[1B"); //cursor moves down 1 time
		printf("\x1B[4D"); //cursor moves left 4 times
	}
	//Set cursor at the right bottom of outer square
	printf("\x1B[1B");
	printf("\x1B[8C");
}

void charSquare(int ch,int type){
	int i,j;
	//White square
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			printf("\x1B[47m  ");
			printf("\x1B[0m"); //Reset code
		}
		printf("\x1B[6D"); //cursor moves left 6 times
		printf("\x1B[1B"); //cursor moves down 1 time
		
	}
	//set cursot at the start of inner square
	printf("\x1B[1A");
	printf("\x1B[4C");

	//loop of binary representation of character
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			//check in a black square
			if(ch%2==1){
				printf("\x1B[%dm  ",type);
				printf("\x1B[0m"); //Reset code
			}else{
				printf("\x1B[2C"); //cursor moves right 2 times
			}
			ch= (ch/2);
			if(j<3){
				printf("\x1B[4D"); //cursor moves left 4 times
			}else{
				printf("\x1B[1A"); //cursor moves up 1 time
				printf("\x1B[2C"); //cursor moves right 2 times
				
			}
		}

	}
	printf("\x1B[1B"); //set cursor to char sq's top right corner
	printf("\x1B[2C");
}

void shortQR(unsigned char shortHashFinal[],int length,int type){
	int i,j,k,l,m,n;
	//White background 20x20 square
	for(i=1;i<=20;i++){
		for(j=1;j<=20;j++){
			printf("\x1B[47m  ");
			printf("\x1B[0m"); //Reset code
		}
		printf("\x1B[1B");//cursor moves down one time
		printf("\x1B[40D"); //cursor moves left 40 times
	}
	//set cursor to start of QR code
	printf("\x1B[19A"); //cursor moves up 19 times
	printf("\x1B[2C"); //cursor moves right 2 times
	
	//call position square function
	positionSquare(type);
	
	//set cursor to top right corner of position square
	printf("\x1B[5A");

	//Print characters 17-20
	k=16;
	for(i=1;i<=2;i++){
		for(j=1;j<=2;j++){
			charSquare(shortHashFinal[k],type);
			k=k+1;
		}
		printf("\x1B[3B"); //cursor moves down 3 times
		printf("\x1B[12D"); //cursor moves left 12 times
	}

	l=0;
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			charSquare(shortHashFinal[l],type);
			l=l+1;
		}
		if(i<4){
			printf("\x1B[3B"); //cursor moves down 3 times
			printf("\x1B[24D"); //cursor moves left 24 times

		}else{
			printf("\x1B[15A"); //cursor moves up 18 times
			printf("\x1B[12D"); //cursor moves 12 times left
		}
	}
	positionSquare(type);

	//set cursor to print characters 21-24
	printf("\x1B[1B"); //cursor moves 1 time down
	printf("\x1B[36D"); //cursor moves left 36 times

	m=20;
	for(i=1;i<=2;i++){
		for(j=1;j<=2;j++){
			charSquare(shortHashFinal[m],type);
			m=m+1;
		}
		printf("\x1B[3B"); //cursor moves down 3 times
		printf("\x1B[12D");
	}
	positionSquare(type);

	//set cursor to left bottom corner of QR code
	printf("\x1B[2B");
	printf("\x1B[12D");
	
}

void longQR(unsigned char longHashFinal[],int length,int type){
	int i,j,k,l,m,n;
        //White background 38x38 square
        for(i=1;i<=38;i++){
                for(j=1;j<=38;j++){
                        printf("\x1B[47m  ");
                        printf("\x1B[0m"); //Reset code
                }
                printf("\x1B[1B");//cursor moves down one time
                printf("\x1B[76D"); //cursor moves left 76 times
        }
	
        //set cursor to start of QR code
        printf("\x1B[37A"); //cursor moves up 37 times
        printf("\x1B[2C"); //cursor moves right 2 times

        //call position square function
        positionSquare(type);

        //set cursor to top right corner of position square
        printf("\x1B[5A");

        //Print characters 101-116
        k=100;
        for(i=1;i<=2;i++){
                for(j=1;j<=8;j++){
                        charSquare(longHashFinal[k],type);
                        k=k+1;
                }
                printf("\x1B[3B"); //cursor moves down 3 times
                printf("\x1B[48D"); //cursor moves left 48 times

        }
	
	//print chararcters 1-100
        l=0;
        for(i=1;i<=10;i++){
                for(j=1;j<=10;j++){
                        charSquare(longHashFinal[l],type);
                        l=l+1;
                }
                if(i<10){
                        printf("\x1B[3B"); //cursor moves down 3 times
                        printf("\x1B[60D"); //cursor moves left 60 times

                }else{
                        printf("\x1B[33A"); //cursor moves up 33 times
                        printf("\x1B[12D"); //cursor moves 12 times left
                }
        }
        positionSquare(type);

        //set cursor to print characters 117-132
        printf("\x1B[1B"); //cursor moves 1 time down
        printf("\x1B[72D"); //cursor moves left 72 times

        m=116;
        for(i=1;i<=8;i++){
                for(j=1;j<=2;j++){
                        charSquare(longHashFinal[m],type);
                        m=m+1;
                }
                printf("\x1B[3B"); //cursor moves down 3 times
                printf("\x1B[12D"); //cursor moves left 12 times
        }
        positionSquare(type);

        //set cursor to left bottom corner of QR code
        printf("\x1B[2B");
        printf("\x1B[12D");

}



