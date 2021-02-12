#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class phase1
{
    public:
        ifstream infile;
        fstream outfile;
        void init();
        void LOAD();
        void Execute();
        void MOS();
        char M[100][4];
        char IR[4];
        char R[4];
        int IC;
        int SI;
        int C;
        char buffer[44];
};

/********************************************************************************************************************************************************************************/

void phase1::init()
{

    for(int i = 0; i<100; i++)
    {
        for(int j = 0; j<4; j++ )
        {
            M[i][j]=' ';

        }

    }
    IR[0]={' '};
    R[0]={' '};
    IC=0;


}

/********************************************************************************************************************************************************************************/

void phase1::MOS()
{

    if(SI == 1)
    {
        for(int i=0;i<=43;i++)
           buffer[i]='\0';

       // cout<<"\nTHis is line\n"<<endl;
        infile.getline(buffer,44);



        int k = 0;
        int i = (IR[2]-48)*10; // converting ASCII value to int
        for( int l=0 ; l<10 ;l++)
        {
            for(int j=0;j<4;j++)
            {
                M[i][j] = buffer[k];
                k++;
            }
             if(k == 44)
            {
                break;
            }
            i++;
        }

      /*  for(int i = 0; i<100; i++)
        {
            cout<<"M["<<i<<"]\t";
            for(int j = 0; j<4; j++ )
            {
                cout<<M[i][j];
            }
            cout<<endl;
        }*/
    }
    else if(SI == 2)
    {
      for(int i=0;i<=43;i++)
           buffer[i]='\0';

        int k = 0;
        int i = (IR[2]-48)*10;


        for( int l=0 ; l<10 ;  l++)
        {
            for(int j = 0 ; j<4; j++)
            {
                buffer[k]=M[i][j];
                outfile<<buffer[k];
                k++;
            }
            if(k == 44)
            {
                break;
            }
            i++;
        }

        outfile<<"\n";
        cout<<buffer;

    }
    else if(SI == 3)
    {

        outfile<<"\n";
        outfile<<"\n";
    }

}

/********************************************************************************************************************************************************************************/

void phase1::Execute()
{
    while(true)
    {
        for(int i = 0; i<4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        if(IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if(IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if(IR [0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
        else if(IR[0]=='L' && IR[1]=='R')
        {
            int i=IR[2]-48;
            i=i*10+(IR[3]-48);
            for(int j=0;j<=3;j++)
                R[j]=M[i][j];
           //for(int j=0;j<=3;j++)
               //cout<< R[j];
                cout<<endl;
        }
        else if(IR[0]=='S' && IR[1]=='R')
        {
            int i=IR[2]-48;
            i=i*10+(IR[3]-48);
            for(int j=0;j<=3;j++)
                M[i][j]=R[j];
         //  for(int j=0;j<=3;j++)
           //     cout<< R[j];
                cout<<endl;
        }
        else if(IR[0] == 'C' && IR[1] == 'R')
        {
            int count=0;
              int i = IR[2]-48;
              i = i*10 +( IR[3]-48) ;
              for(int j=0;j<=3;j++)
                if(M[i][j] == R[j])
                    count++;

            if(count==4)
                C=1;
              cout<<C;
        }
         else if(IR[0] == 'B' && IR[1] == 'T')
         {
             if(C== 1)
             {
                int i = IR[2]-48;
                i = i*10 +( IR[3]-48) ;

                IC = i;

             }
         }
    }
}

/********************************************************************************************************************************************************************************/

void phase1::LOAD()
{

    cout<<"Reading Data..."<<endl;
    int i = 0;
    do
    {
        for(int i=0;i<=43;i++)
            buffer[i]='\0';

        infile.getline(buffer,44);


        if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
	}
        else if(buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            IC = 00;
            Execute();

        }
        else if(buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            i=0;
            cout<<"\n\nAfter end of program\n\n";
            for(int s = 0; s<100; s++)
            {
                cout<<"M["<<s<<"]\t";
                for(int j = 0; j<4; j++ )
                {
                    cout<<M[s][j];
                }
                cout<<endl;
            }
            continue;
        }
        else{

            int k=0;
            for(; i <100; ++i)
            {
                for(int j = 0 ; j<4; ++j)
                {
                    M[i][j] = buffer[k];
                    k++;
                }
                if(k == 44 || buffer[k] == ' ' || buffer[k] == '\n')
                {
                    break;
                }
            }
        }

    }while(!infile.eof()) ;

}

/********************************************************************************************************************************************************************************/

int main()
{
    phase1 p;

    p.infile.open("a.txt", ios::in);
    p.outfile.open("output1.txt", ios::out);

    if(!p.infile)
    {
        cout<<"File does not exist"<<endl;
    }
    else
    {
        cout<<"File Exist"<<endl;
    }

    p.LOAD();

    return 0;
}
