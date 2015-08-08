

/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -Alex Lui,Tewoldebrhan Hagos,Khachatur Mirijanyan
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <set>
#include "Exception.h"
#include "Disjoint_sets.h"



class Weighted_graph {
private:
    static const double INF;
    
    // Do not implement these functions!
    // By making these private and not implementing them, any attempt
    // to make copies or assignments will result in errors
    Weighted_graph( Weighted_graph const & );
    Weighted_graph &operator=( Weighted_graph );
    
    // your choice
    double **matrix;
    int edges_total;
    int *degrees;
    int max_vert;
    int verticies_total;
    
    
    
    typedef struct {
        int v1;
        int v2;
        double weight;
    } edge_t;
    
public:
    Weighted_graph( int = 10 );
    ~Weighted_graph();
    
    int degree( int x ) const;
    int edge_count() const;
    std::pair<double, int> minimum_spanning_tree() const;
    
    bool insert_edge( int, int, double );
    bool erase_edge( int, int );
    void clear_edges();
    bool check_edge(int i, int j);
    
    // Friends
    
    friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int n ) {
    if (n<0)
        throw illegal_argument();
    
    degrees=new int [n];
    
    for (int i=0; i<n; i++)
    {
        degrees[i]=0;
    }
    
    matrix= new double *[n];
    
    for (int i=0; i<n; i++)
        matrix[i]=new double[n];
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            matrix[i][j]=INF;
        }
        matrix[i][i]=0;
    }
    max_vert=n;
    edges_total=0;
    verticies_total=0;
        
}

Weighted_graph::~Weighted_graph() {
    delete [] degrees;
    for (int i=0; i<max_vert; i++)
        delete []matrix[i];
    delete [] matrix;
}

int Weighted_graph::degree( int x ) const{
    if (x<0 || x>verticies_total)
        throw illegal_argument();
    return degrees[x];
}

int Weighted_graph::edge_count() const{
    return edges_total;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    
    if (i<0||j<0||i>=max_vert||j>=max_vert||d<0)
        throw illegal_argument();
    
    if (i<max_vert && j<max_vert && d>0 && i!=j)
    {
        if (matrix[i][j]!=INF)
        {
            edges_total--;
            degrees[i]--;
            degrees[j]--;
            verticies_total--;
        }
        matrix[i][j]=d;
        matrix[j][i]=d;
        edges_total++;
        degrees[i]++;
        degrees[j]++;
        verticies_total++;
        
        return true;
    }
    return false;
}

bool Weighted_graph::erase_edge(int i, int j){
    if (i<0||j<0|| j>=max_vert||i>=max_vert)
        throw illegal_argument();
    if (matrix[i][j]!=INF)
    {
        matrix[i][j]=INF;
        verticies_total--;
        return true;
    }
    return false;
}

bool Weighted_graph::check_edge(int i, int j){
    if (i<0||j<0|| j>=max_vert||i>=max_vert)
        throw illegal_argument();
        if (matrix[i][j]!=INF)
            return true;
    return false;
}

void Weighted_graph::clear_edges()
{
    for (int i=0; i<max_vert; i++)
    {
        degrees[i]=0;
        
    }
    
    for (int i=0; i<max_vert; i++){
        for (int j=0; j<max_vert; j++){
            matrix[i][j]=INF;
        }
        matrix[i][i]=0;
    }
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    

    double count=0.0;
    int a=0;
    edge_t array[max_vert*max_vert];
    for (int i=0; i<max_vert; i++){
        for (int j=0; j<max_vert; j++){
            if (i<j){
                if(matrix[i][j]!=INF && matrix[i][j]!=0)
                {
                    edge_t test;
                    test.v1=i;
                    test.v2=j;
                    test.weight=matrix[i][j];
                    array[a]=test;
                    a++;
                }
        }
    }
    }
    
    //insertion sort, should have used faster sorting algorithm
    int b, c;
    edge_t key;
    for (c=1; c<verticies_total; c++)
    {
        key=array[c];
        for (b=c-1; (b>=0) && (array[b].weight>key.weight); b--)
        {
            array[b+1]=array[b];
        }
        array[b+1]=key;
    }
    int visits=0;
    
    Data_structures::Disjoint_sets test( max_vert );
    
    for (int i=0; i<verticies_total; i++)
    {
        if ((test.find(array[i].v1)!=(test.find(array[i].v2))))
        {
            count+=array[i].weight;
            test.set_union(array[i].v1, array[i].v2);
        }
        visits++;
        if (test.disjoint_sets()==1)
            break;
        
    }
    
    return std::pair<double, int>( count, visits);
}



std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    // Your implementation
    
    return out;
}

#endif
