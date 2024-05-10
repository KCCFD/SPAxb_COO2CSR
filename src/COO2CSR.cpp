#include <bits/stdc++.h>

using namespace std;


std::vector<int> COL, ROW, ROW_ptr;
std::vector<double> VAL, b, x;


int m; //matrix size
double nnz; //total no: of non-zeros in matrix


int    f_argc;
char **f_argv;


void meshread_COO()
{

	fstream fin;
	fin.open(f_argv[1], ios::in);
	if(fin.fail())
		cerr<<"Error!! No Grid file found!!!"<<endl;


	int row_id, col_id;
	double val;
	int count = 0;

	
	const char *MATSTART1="MATSTART_1";
	const char *MATSTART0="MATSTART_0";
	int res1 = std::strcmp(MATSTART1, f_argv[3]);
	int res2 = std::strcmp(MATSTART0, f_argv[3]);

	cout<<"f_argv[3]\t"<<f_argv[3]<<endl;
	
	while(fin>>row_id>>col_id>>val)
	{
		if(res1==0)
		{
		ROW.push_back(row_id-1); //MATLAB matrix index starts at 1 not 0
		COL.push_back(col_id-1);
		}
		else if(res2==0)
		{
		ROW.push_back(row_id); 
		COL.push_back(col_id);
		}
		else
		cerr <<"Error!! Bad argument!! Should provide either MATSTART_0 or MATSTART_1"<<endl;
		VAL.push_back(val);
		if(row_id==col_id)
		count++;
	}

	fin.close();
	assert(COL.size()==VAL.size());
	assert(ROW.size()==VAL.size());

	m=count;
	nnz=VAL.size();
	cout<<"Matrix size : "<<m<<"\t no: of non-zeros : "<<nnz<<endl;


}



void matset_CSR()
{
	int n=1;
	ROW_ptr.push_back(0);
	for(int i=1; i<nnz; i++)
	{

		if(ROW[i]!=ROW[i-1])
		{
			ROW_ptr.push_back(i);
		n++;
		}

	}
	ROW_ptr.push_back(nnz);



/** Arrange array in ascending order starting from left end of row **/
// CELL-NEIGHBOUR data need to be sorted in ascending order for each row in matrix //
for(int i=0;i<n;i++)
{

int temp;
double temp1;
for(int j=ROW_ptr[i];j<=ROW_ptr[i+1]-1;j++)
{

temp=0;
temp1=0.0;
for(int k=j+1;k<=ROW_ptr[i+1]-1;k++)
{
if(COL[j]>COL[k])
{
temp=COL[j];
temp1=VAL[j];
COL[j]=COL[k];
VAL[j]=VAL[k];
COL[k]=temp;
VAL[k]=temp1;
}
}

}
}



}

void matCSR_out()
{
	fstream fout;
	fout.open(f_argv[2], ios::out);

	fout<<"'COL_ind'   'VAL'\n"<<endl;
	for(int i=0; i<nnz; i++)
	{
		fout<<COL[i]<<"\t"<<VAL[i]<<endl;
	}

		fout<<"\n'ROW_pointer'\n"<<endl;

	for(int i=0; i<m+1; i++)
	{
		fout<<ROW_ptr[i]<<endl;
	}
	fout.close();
}


void matROW_destroy()
{

	std::vector<int>().swap(ROW);

}


int main(int argc, char **argv)
{

	f_argc = argc;
    	f_argv = argv;

	cout <<"No. of arguments: "<<argc<<"\t Path to Mat_COO.dat : "<<f_argv[1]<<endl;

	meshread_COO();
	matset_CSR();
	matCSR_out();
	matROW_destroy();

}
