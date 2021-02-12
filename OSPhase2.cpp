#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctime>
#include<fstream>
#include<cstdlib>

using namespace std;

class PCB
{
   public:
    char s[41];
    int ttl;
    int tll;
    int ttc;
    int llc;
};
 
class OS{
    private:
        int used[30]; //////////used for marking
        int loopir;
        int IC = 0, SI = 0, c = 0, m = 0, TI = 0, PI = 0;
        char R[4], M[300][4], IR[4];
        char d = '\0';
        int flag = 1;
        int frame = 0;      ////frame table geneRAtor
        int g = 0;          ////used in initframetable
        int f = 0;          ///for updating frametable
        int n = 3;          //used for storing the frame in pagetable entry
        int PTR = 0, h = 0; ///Page table Register
        int q = 0, l = 0;
        int y = 0, s = 0;
        int b = 3;
        int x = 0, w = 0;
        int rr = 0, e = 0, mm = 0;
        int z = 0;           //Random function VAriable
        
    public:
        void init();
        void load();
        void MOS();
        void Execute();
        void read();
        void write();
        void terminate(int);
        int ALLOCATE();
        void initframetable(int);
        void StartExecution();
        int addressmap(int);
        void simulation();
        char buff[41];
        PCB p;
        FILE * infile,*outfile;
};


int main()
{
    OS os;
    int i = 0, j = 0;
     
    os.infile = fopen("input.txt", "r");
    os.outfile = fopen("output.txt", "w");

    if(!os.infile)
    {
        cout<<"File Does not exist"<<endl;
    }
    else
    {
        cout<<"File Exist"<<endl;
    }

    os.load();
    /*for(i=PTR;i<(PTR+10);i++){
        printf("\nPagetable[%d]=",i);
        for(j=0;j<4;j++){
            printf("%c",M[i][j]);
        }
    }*/
}


int OS::ALLOCATE()
{
    cout<<"in AlLOCATE"<<endl;
    
    z = rand() % 30;
    if (used[z] == 0)
    {
        used[z] = 1;
        return z;
    }

    else
    {
        return ALLOCATE();
    }
}


void OS::initframetable(int frame)
{
    cout<<"In initframetable"<<endl;
    int i, j;
    g = frame;
    y = (g * 10);
    for (i = y; i < (y + 10); i++)
    {
        for (j = 0; j < 4; j++)
        {
            M[i][j] = '*';
        }
    }
    cout<<"end of initframetable"<<endl;
}

void OS::load()
{
    cout<<"In Load"<<endl;
    int m = 0, z = 0, i = 0, j = 0, IC = 0;

    while (fgets(buff, 41, infile) != NULL)
    {


        int k = 0;
        if (buff[0] == '$' && buff[1] == 'A' && buff[2] == 'M' && buff[3] == 'J')
        {
            e = (((buff[8] - '0') * 1000) + ((buff[9] - '0') * 100) + ((buff[10] - '0') * 10) + ((buff[11] - '0') * 1));
            mm = (((buff[12] - '0') * 1000) + ((buff[13] - '0') * 100) + ((buff[14] - '0') * 10) + ((buff[15] - '0') * 1));
            cout<<"AMJ detected"<<endl;
            init();
            frame = ALLOCATE();
            PTR = (frame * 10);
            h = PTR;
            initframetable(frame);
            for(int i=0;i<=40;i++)      //clear buffer
                buff[i]='\0';
        }
        else if (buff[0] == '$' && buff[1] == 'D' && buff[2] == 'T' && buff[3] == 'A')
        {
            cout<<"$DTA detected"<<endl;
            StartExecution();
            for(int i=0;i<=40;i++)      //clear buffer
                buff[i]='\0';
        }
        else if (buff[0] == '$' && buff[1] == 'E' && buff[2] == 'N' && buff[3] == 'D')
        {
            cout<<"continue\n";
            for(int i=0;i<=40;i++)      //clear buffer
                buff[i]='\0';
        }
        else if(buff[0]=='G'||buff[0]=='P')
        {
            cout<<"reading..."<<endl;
            m = ALLOCATE();
            q = (m * 10);
            while (m > 0)
            {
                M[h][b] = ((m % 10) + '0');
                b = b - 1;
                m = m / 10;
            }
            h = (h + 1);
            b = 3;
            for (i = q; i < (q + 11); i++)
            {

                for (j = 0; j < 4; j++)
                {
                    M[i][j] = buff[k];
                    k++;
                }
				if(k == 40)
					break;

               
            }

            for(int i = 0; i<300; i++)
			{ 
				cout<<"M["<<i<<"]\t";
				for(int j = 0; j<4; j++ )
				{  
					cout<<M[i][j];
				}
				cout<<endl;
			} 
            /*for (i = q; i < (q + 10); i++) {
                printf("\n");
                printf( "M[%d]=", i);
                for (j = 0; j < 4; j++){
            		printf("%c", M[i][j]);
                }
            }
        */
            for(int i=0;i<=39;i++)      //clear buffer
                buff[i]='\0';
        }
    }
}


void OS::init()
{
    cout<<"IN init"<<endl;
   
    for(int i = 0; i<300; i++)
    {    
        for(int j = 0; j<4; j++ )
        {  
            M[i][j]=' ';
            
        }   
    }
    int i = 0, j = 0;
    IC = 0;
    SI = 0, PI = 0, TI = 0;
    p.ttl = e;
	cout<<"TTL :"<<p.ttl<<endl;
    p.tll = mm;
	cout<<"TLL :"<<p.tll<<endl;
    p.ttc = 0;
    p.llc = 0;
    for (i = 0; i < 30; i++)
    {
        used[i] = 0;
    }
}


void OS::StartExecution()
{
    IC = 0, TI = 0, PI = 0, SI = 0;
    Execute();
}


void OS::Execute()
{
    int i = 0, j = 0, o = 0, a = 0, b = 0, c = 0, g = 0;
    i = addressmap(IC);
    for (j = 0; j < 4; j++)
    {
        IR[j] = M[i][j];
    }
    if (IR[0] == 'H')
    {
        simulation();
        SI = 3;
        MOS();
    }
    if (IR[2] - '0' == (-38))
    {
        IC = IC + 1;
        Execute();
    }

    if ((IR[0] != 'G') && (IR[0] != 'P') && (IR[0] != 'L') && (IR[0] != 'S') && (IR[0] != 'C') && (IR[0] != 'H') && (IR[0] != 'B'))
    {
        PI = 2;
        MOS();
        exit(0);
    }

    IC = IC + 1;
    a = IR[2] - '0';
    b = IR[3] - '0';
    o = ((a * 10) + b);
    x = addressmap(o);
    if (PI == 0)
    {
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            simulation();
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            simulation();
            MOS();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            for (i = 0; i < 4; i++)
            {
                R[i] = M[x][i];
            }
            simulation();
            Execute();
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            for (i = 0; i < 4; i++)
            {
                M[x][i] = R[i];
            }
            simulation();
            Execute();
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            while (rr < 4)
            {
                if (R[rr] == M[x][rr] && flag == 1)
                {
                    flag = 1;
                    rr = (rr + 1);
                }
                else
                {
                    flag = 0;
                    rr = (rr + 1);
                }
            }
            if (flag == 1)
            {
                flag = 1;
            }
            simulation();
            Execute();
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            a = IR[2] - '0';
            b = IR[3] - '0';
            c = ((a * 10) + b);
            simulation();
            if (flag == 1)
            {
                IC = c;
                Execute();
            }
            else if (flag == 0)
            {
                IC = IC + 1;
                Execute();
            }
            simulation();

        } 
        else
        {
            Execute();
        }
    } 

    else if (PI == 3)
    {
        SI = 0;
        MOS();
    }
}


void OS::MOS()
{
    int i = 0, j = 0;
    if (SI == 1 && TI == 0)
    {
        read();
    }

    else if (PI == 3 && TI == 0)
    {
        i = 3;
        w = ALLOCATE();
        while (w > 0)
        {
            M[x][i] = ((w % 10) + '0');
            i = i - 1;
            w = w / 10;
        }
        IC = (IC - 1);
        Execute();
    }
    else if (SI == 2 && TI == 0)
    {
        write();
    }
    else if (TI == 0 && SI == 3)
    {
        SI = 0;
        terminate(0);
        exit(0);
    }
    else if (SI == 1 && TI == 2)
    {
        terminate(3);
        exit(0);
    }

    else if (SI == 2 && TI == 2)
    {
        terminate(3);
        exit(0);
    }
    else if (TI == 2 && SI == 3)
    {
        terminate(0);
        exit(0);
    }

    else if (TI == 0 && PI == 2)
    {
        terminate(5);
        exit(0);
    }

    else if (TI == 2 && PI == 2)
    {
        terminate(5);
        exit(0);
    }
    else if (TI == 2 && PI == 1)
    {
        terminate(4);
        exit(0);
    }

    else if (TI == 0 && PI == 1)
    {
        terminate(4);
        exit(0);
    }
}


int OS::addressmap(int VA)
{
    int fno, RA;
    int pte = (PTR + (VA / 10));
    if (M[pte][2] == '*' && M[pte][3] == '*' && IR[0] == 'G' && IR[1] == 'D')
    {
        PI = 3;
        return pte;
    }

    else if (M[pte][2] == '*' && M[pte][3] == '*' && IR[0] == 'P' && IR[1] == 'D')
    {
        terminate(6);
        exit(0);
    }
    else if (VA < 0 || VA > 99)
    {
        PI = 1;
        MOS();
    }

    else
    {
        if (M[pte][2] == '*')
        {
            fno = (M[pte][3] - '0');
            RA = ((fno * 10) + (VA % 10));
            PI = 0;
            return RA;
        }
        else
        {
            fno = (((M[pte][2] - '0') * 10) + ((M[pte][3] - '0') * 1));
            PI = 0;
            RA = ((fno * 10) + (VA % 10));
            return RA;
        }
    }
    return 0;
}

void OS::read()
{
    int f = 0, i = 0, j = 0, k = 0;
   char s[41];
    f = x;

    fgets(s, 41, infile);
    

    if (s[0] == '$' && s[1] == 'E' && s[2] == 'N')
    {
        terminate(1);
        exit(0);
    }
    else
    {
        for (i = f; i < (f + 10); i++)
            for (j = 0; j < 4; j++)
            {

                M[i][j] = s[k];
                k++;
            }
      /*for (i = f; i < (f + 10); i++){
            printf("\nM[%d]=",i);
            for (j = 0; j < 4; j++) {
                printf("%c",M[i][j]);
            }
        }*/
    
        Execute();
    }
}


void OS::write()
{
    
    int i = 0, j = 0, k = 0;
    char buff[41];
    p.llc = (p.llc + 1);
    if (p.llc <= p.tll)
    {
        for (i = x; i < (x + 10); i++)
        {
            for (j = 0; j < 4; j++)
            {
                buff[k] = M[i][j];
               
                k = k + 1;
            }
            fputs(buff,outfile);
              Execute();
        }

        for(int i = 0; i<300; i++)
        { 
            cout<<"M["<<i<<"]\t";
            for(int j = 0; j<4; j++ )
            {  
                cout<<M[i][j];
            }
            cout<<endl;
        } 
        
      
    }

    else if (p.llc > p.tll)
    {
        terminate(2);
        exit(0);
    }
    p.llc = (p.llc - 1);
}


void OS::terminate(int EM)
{
    
     if(EM==0) {
        fputs("\nNo Error\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=%d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
		
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }

    else if(EM==1) {
        fputs("\nOut of Data Error\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=  %d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }

    else if(EM==2) {
        fputs("\nLine Limit Error\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=%d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
		cout<<"TTL :"<<p.ttl<<endl;
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }

    else if(EM==3) {
        fputs("\nTime Limit Error\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=%d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }

    else if(EM==4) {
        fputs("\nOp Code Error\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=%d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }

    else if(EM==5) {
        fputs("\nOperand Error\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=%d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }

    else if(EM==6) {
        fputs("\nInvalid Page Fault\n",outfile);
        fprintf(outfile,"IC=%d\tTTL=%d\tTLL=%d\tTTC=%d\tLLC=%d\tPI=%d\tTI=%d\tSI=%d\t",IC,p.ttl,p.tll,p.ttc,p.llc,PI,TI,SI);
        fprintf(outfile,"IR=%s\n\n\n",IR);
    }
    load();
}


void OS::simulation()
{
   
    if ((IR[0] == 'G' && IR[1] == 'D') || (IR[0] == 'S' && IR[1] == 'R'))
    {
        p.ttc = p.ttc + 2;
    }
    else
    {
        p.ttc = p.ttc + 1;
    }

    if (p.ttc > p.ttl)
    {
        TI = 2;
        MOS();
    }
    else
    {
        TI = 0;
    }
}
