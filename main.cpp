#include <iostream>
#include <string>
#include<cstring>
#include <fstream>
using namespace std ;
class erorr:public exception   {
public:
    virtual const char* what(){
    cout << "your seq is wrong";
    }
};
class Sequence
{
  	protected:
       string seq;
        int length;
    public:
 	 	// constructors and destructor
 	 	Sequence(){}
       Sequence(string seq1,int length)
       {
          seq = seq1;
          length=sizeof(seq);
        }


        Sequence(Sequence& rhs){
        seq=rhs.seq;
        }
        virtual ~Sequence(){}
 	 	// pure virtual function that should be overridden because every
        // type of sequence has its own details to be printed
        virtual void Print()= 0;
 	 	// friend function that will find the LCS (longest common
        // subsequence) between 2 sequences of any type, according to
        // polymorphism
         bool operator ==(Sequence & se2)
        {

             for(int i=0;i<sizeof(seq);i++){
            if(seq[i]!=se2.seq[i]){
                   return false;
            }

    }

   return true;
}
 /*string operator =(Sequence & seq)
        {

string a;
             for(int i=0;i<sizeof(seq);i++){
            a[i]=seq.seq[i];
                  }

   return a;
}*/
                friend string Align(Sequence * s1, Sequence * s2 );
       };




class RNA;

enum DNA_Type{promoter, motif, tail, noncoding};

class DNA : public Sequence
{
  	private:
        DNA_Type type;
        DNA * complementary_strand;
        int startIndex;
        int endIndex;
    public:
 	 	// constructors and destructor
        DNA()
        {
            type = motif;
    startIndex = 0;
    endIndex = 0;
    seq = "NO";
        }
         DNA(DNA& rhs)
        {

    type = rhs.type;
   seq = rhs.seq;
    startIndex = rhs.startIndex;
    endIndex = rhs.endIndex;
        }
        DNA(char *seq1,int start , int End, DNA_Type type)
        {
    this ->seq = seq;
    startIndex = start;
    endIndex = End;
    this-> type = type;

        }

        DNA(string seq,int s , int E)
{
    this ->seq = seq;
    startIndex = s;
    endIndex = E;
}

        ~DNA(){}
       string getseq()
        {
            return seq;
        }

        // function to convert the DNA sequence to RNA sequence
        // It starts by building the complementary_strand of the current
        // DNA sequence (starting from the startIndex to the endIndex), then,
        // it builds the RNA corresponding to that complementary_strand.
       /* RNA ConvertToRNA()

        {
            char * n;
           n= new char[sizeof(seq)];

             complementary_strand = new DNA ();
            complementary_strand->seq = seq ;

        for(int i=startIndex-1;i<endIndex; ++i){
        if(seq[i] == 'T' )
            seq[i] = 'U';
            n[i]=+seq[i];

}

     return RNA(n,mRNA)
        }*/
 	 	// function to build the second strand/pair of DNA sequence
	    // To build a complementary_strand (starting from the startIndex to
        // the endIndex), convert each A to T, each T to A, each C to G, and
        // each G to C. Then reverse the resulting sequence.
        void BuildComplementaryStrand()
        {
          complementary_strand = new DNA ();
          complementary_strand->seq = seq;
    for(int i = startIndex; i < endIndex; ++i)
    {
        if(seq[i] == 'A' )
            complementary_strand->seq[i] = 'T';
        if(seq[i] == 'T' )
            complementary_strand->seq[i] = 'A';
        if(seq[i] == 'G' )
            complementary_strand->seq[i] = 'C';
        if(seq[i] == 'C' )
            complementary_strand->seq[i] = 'G';
    }
        cout << complementary_strand->seq << endl;

        }
         	 	// function printing DNA sequence information to user

void Print()
{
    cout<< "Type: " << type << endl
         << "DNA Seq: " << seq<< endl;
}

ostream & operator <<(ostream &Out)
{
    DNA dna;
    Out << "Type: " << dna.type << endl
        << "DNA Seq: " << dna.seq << endl;

    return Out;
}

void Align( string X, string Y, int m, int n )
{
   int L[m+1][n+1];

   /* Following steps build L[m+1][n+1] in bottom up fashion. Note
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (int i=0; i<=m; i++)
   {
     for (int j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;
       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }

   // Following code is used to print LCS
   int index = L[m][n];

   // Create a character array to store the lcs string
   char lcs[index+1];

   // Start from the right-most-bottom-most corner and
   // one by one store characters in lcs[]
   int i = m, j = n;
   while (i > 0 && j > 0)
   {
      // If current character in X[] and Y are same, then
      // current character is part of LCS
      if (X[i-1] == Y[j-1])
      {
          lcs[index-1] = X[i-1]; // Put current character in result
          i--; j--; index--;     // reduce values of i, j and index
      }

      // If not same, then find the larger of two and
      // go in the direction of larger value
      else if (L[i-1][j] > L[i][j-1])
         i--;
      else
         j--;
   }

   // Print the lcs
  cout << "LCS of " << X << " and " << Y << " is " << lcs;

}


};



class Protein;

// struct representing a codon of 3 DNA/RNA characters and ‘\0’
struct Codon
{
  	string value[4];    	    // 4th location for null character
    string AminoAcid;  	    // corresponding AminoAcid according to Table
};

// need to create one object of that class to load the AminoAcids table
// into memory
class CodonsTable
{
  	private:
        Codon codons[64];
   	public:
 	 	// constructors and destructor
        CodonsTable()
        {

        }
        ~CodonsTable(){}
 	 	// function to load all codons from the given text file
        void LoadCodonsFromFile()
    {
        ifstream file;
        file.open("table.txt");

            string t;
            string c;
            int x = 0;
            while (file >> t && file >> c)
            {
                codons[x].AminoAcid = c;
                codons[x].value[0] = t[0];
                codons[x].value[1] = t[1];
                codons[x].value[2] = t[2];
                ++x;
            }

    }
    /* Codon getAminoAcid(string value){
       for(int i = 0; i < 64; ++i)
    {
        cout << codons[i].value << endl;
       if(value == codons[i].value)
       {
                cout << "k" << endl;
            return codons[i].AminoAcid;
        }}}*/

     /*   void setCodon(string value, string AminoAcid, int index)
        {
    codons[index].value = value;
    codons[index].AminoAcid = AminoAcid;
}*/
};

enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};

class RNA : public Sequence
{
  	private:
        RNA_Type type;
         int startIndex;
        int endIndex;
  	public:
 	 	// constructors and destructor
        RNA()
        {
             startIndex = 0;
            endIndex = 0;
            type = mRNA;

        }
        RNA(string seq, RNA_Type atype)
        {
            this-> seq = seq;
            this-> type = atype;
        }
        RNA(RNA& rhs)
        {
            seq = rhs.seq;
            type = rhs.type;
            startIndex = rhs.startIndex;
           endIndex = rhs.endIndex;
        }

 	 	// function to be overridden to print all the RNA information
        void Print()
        {
           cout << "Type: " << type << endl<< "DNA Seq: " << seq << endl;
        }
        string GetSeq()
{
    return seq;
}
 	 	// function to convert the RNA sequence into protein sequence
        // using the codonsTable object
    //    Protein ConvertToProtein(const CodonsTable & table);
 	 	// function to convert the RNA sequence back to DNA
        /*DNA ConvertToDNA()
         {

            string M="";

        for(int i=startIndex;i<endIndex; ++i){
        if(seq[i] == 'U' )
            seq[i] = 'T';
            M[i]=+seq[i];

}

     return DNA(M,promoter);

        }*/
       /* Protein ConvertToProtein( CodonsTable & table)
{
    string st = "";
    string st2 = "";
    for(int i = 0; i <= seq.length(); ++i)
    {
        if( i % 3 == 0 && i != 0)
        {
            st2 += table.getAminoAcid(st);
            st = "";
        }
        st += seq[i];
    }
    return Protein(st2);
}*/

 ostream & operator << (ostream &Out)
{
    RNA rna;
    Out << "Type: " << rna.type << endl
        << "RNA Seq: " << rna.seq << endl;
    return Out;
}
};

enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};

class Protein : public Sequence
{
  	private:
        Protein_Type type;
      public:
 	 	// constructors and destructor
 	 	Protein()
{
    type = Cellular_Function;
    seq = "";

}
 	 	Protein(string p)
{
    seq = p;

}

 		//~Protein{}

 	 /*	ostream & operator << (ostream &Out)
{
    Protein pr;
    Out << "Type: " << pr.type << endl
        << "Protein Seq: " << pr.seq << endl
        << "*****************************************" << endl;
    return Out;
}*/

 	 	// return an array of DNA sequences that can possibly
                // generate that protein sequence
           DNA* GetDNAStrandsEncodingMe(const DNA & bigDNA){
    DNA dn(bigDNA);
    RNA rn ( dn.ConvertToRNA());
    CodonsTable co;
    co.LoadCodonsFromFile("table.txt");
    DNA * dnPointer = new DNA[100];
    int counter = 0;
cout << dn.ConvertToRNA() << endl;
for (int i = 0; i < rn.seq.length(); ++i)
    {
        string st = "";
        string st2 = "";
//cout << " iuytr" << endl;
        int k = 0;
        for(int j = 0; j < seq.length() * 3; ++j)
        {
            st += rn.GetSeq()[j];
                      ///  cout << st <<endl;

            if((j+1) % 3 == 0)
            {                        //cout << st <<endl;
               /// cout << (co.getAminoAcid(st) == seq[k]) << endl << endl << endl;
               cout << co.getAminoAcid(st)<< endl << endl <<endl;

               if( co.getAminoAcid(st) != seq[k])
               {
                   break;
               }
                 if(co.getAminoAcid(st) == seq[k])
               {
                   st2 += st;
                  // cout << st2 << endl;
               }
               st = "";
               ++k;
               cout << st2 << endl;

            }
        }
        if (st2.length() == seq.length() * 3)
        {
          RNA rn2(st2, mRNA);
           DNA dn2("", 1, st2.length() ,promoter);
           dn2 = rn2.ConvertToDNA();
           dnPointer[counter] = dn2;
           counter ++;
           i = (seq.length() * 3) - 1;
           cout << dn2 << endl;
        }
           }
           }
};

int main()
{
try
{
    cin >> seq ;
}
catch (error er)
{
    cout << er.what()<< endl ;
}
/*DNA d("asdf",0,2);
d.BuildComplementaryStrand();
d.Align("asdfg","asdfg",6,6);*/

  return 0;

}
