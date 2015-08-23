author@Ashutosh


#include<stdio.h>
#include<stdlib.h>
int i,n,data[1024],count,key[1024],rec_basis[1024];

//data[] -> actual data to be sent,
//key[] -> final key
//rec_basis[] -> temporary storage of received basis


char tranz_data[1024],renz_data[1024],key_data[1024];

//tranz_data -> used for transmitter's encoded data
//renz_data -> used for recieived qbits
//key_data -> used for matched qbits


time_t t;
int temp[1024],man,freq,rec;

//temp[] -> used for random generation 0 and 1 for data loss
//freq -> n*prob


float prob;


//generation of data

void random_zen()
{
    srand((unsigned) time(&t));
    printf("Enter the no. of photons you want to send\n\n");
    scanf("%d",&n);
    printf("\n\nIf you want to insert the photons manually 'press 1' otherwise press any other key\n\n");
    scanf("%d",&man);
    printf("\n\nData to be sent                : ");
    if(man==1)     //manual entry of data
   {
       printf("\n\nEnter the elements manually : \t");
       for(i=0; i<n; i++)
        {
            scanf("%d",&data[i]);
        }
   }

   else           //random generation of data
    for(i=0; i<n; i++)
    {
        data[i]=rand()%2;
    }
    for(i=0; i<n; i++)
    printf("%d ",data[i]);
    printf("\n");

}



//creating an array for random generation of 0 and 1 for data loss

void fillup()
{
    srand((unsigned) time(&t));
    prob=rand()%10;
    prob/=10;

    //printf("Enter the probability of data loss\n\n");
    //scanf("%f",&prob);

    freq=(prob*n);
    for(i=0; i<n; i++)
    {
        if(i<freq)
            temp[i]=0;
        else
            temp[i]=1;
    }
}


//Encoding of the data at the transmitter

void trans_data()
{
    srand((unsigned) time(&t));  //random generation of data on the basis of time internally built
    printf("\n\nHere '+' signifies Rectilinear Basis \n     'x' signifies Diagonal Basis\n");
    printf("Basis used at the transmitter :  ");
    for(i=0; i<n; i++)
    {
        rec=rand()%2 + 4;
        if(rec==4)
            printf("+ ");
       else
        printf("x ");
        if(rec==4 && data[i]==0)
            tranz_data[i]='[';
        if(rec==4 && data[i]==1)
            tranz_data[i]=']';
        if(rec==5 && data[i]==0)
            tranz_data[i]='<';
        if(rec==5 && data[i]==1)
            tranz_data[i]='>';
    }
    printf("\n\nHere basis used are \n\n'[' = Rectilinear Basis '0'\n']' = Rectilinear Basis '1'\n'<' = Diagonal Basis '0'\n'>' = Diagonal Basis '1'\n\n");

    printf("\n\nEncoded data                   : ");

    for(i=0; i<n; i++)
        printf("%c ",tranz_data[i]);





}


//received data at the receiver


void recdata()
{
     srand((unsigned) time(&t));
     for(i=0; i<n; i++)
    {
        rec=temp[rand()%n];
        printf("%d ",rec);
        if(rec==0)
        {
                renz_data[i]='-';
                rec_basis[i]=0;
        }
        else
        {
            rec=rand()%2 + 4;
            rec_basis[i]=rec;
            if(rec==4 && data[i]==0)
            renz_data[i]='[';
            if(rec==4 && data[i]==1)
            renz_data[i]=']';
            if(rec==5 && data[i]==0)
            renz_data[i]='<';
            if(rec==5 && data[i]==1)
            renz_data[i]='>';

        }


    }
    printf("\n\nBasis used at the receiver     : ");
    for(i=0; i<n; i++)   //basis used at the receiver
    {
            if(rec_basis[i]==0)
                printf("- ");
            else if(rec_basis[i]==4)
            printf("+ ");
            else
                printf("x ");
    }
    printf("\n\nReceived data                  : ");
    for(i=0; i<n; i++)
    printf("%c ",renz_data[i]);
    printf("\n\n");
}


//comparison of the basis and generation of key

void keyzen()
{
    count=0;
    for(i=0; i<n; i++)
    {
        if(tranz_data[i]==renz_data[i])
        {
            key_data[i]=tranz_data[i];
            if(tranz_data[i]=='[' || tranz_data[i]=='<')
                key[count]=0;
            else if(tranz_data[i]==']' || tranz_data[i]=='>')
            key[count]=1;
            count++;
        }
        else
            key_data[i]=' ';
    }
    printf("The matched photons are        : ");
    for(i=0; i<n; i++)
    printf("%c ",key_data[i]);
    printf("\n\nBy comparing the basis used at both ends the mismatched are discarded ");
    printf("\n\nThe obtained key is            : ");
    for(i=0; i<count; i++)
    printf("%d ",key[i]);
    printf("\n\n");

}
main()
{
    label:
    while(1)
    {
         random_zen();
    printf("\n\n");
    fillup();
    printf("\n\n");
    trans_data();
    printf("\n\nData loss in the channel due to external effect is %.2f\n\n",prob);
    printf("\n\n");
    printf("Here for reference '0' means loss of data and '1' signifies received data\n");
    printf("\n\n");
    printf("                                 ");
    recdata();
    printf("\n\n");
     if(prob > 0.5)
    {
        printf("The channel has experienced heavy data loss, the reason may be intruder! \n                              Please resend the data");
        printf("\n\n");printf("\n\n");
        goto label;
    }
     printf("\n\n");
    keyzen();

    }

}


