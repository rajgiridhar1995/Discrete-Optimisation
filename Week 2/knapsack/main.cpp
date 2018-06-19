#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

// global variables
unsigned int i, j, n, K, temp_v, temp_w;	// Number of items and Capacity are Non-negative
vector<pair<pair<int,int>,int> > Item;

typedef struct Node {
  int value, room, depth,estimate;
  bool selected;
  struct Node* leftS;
  struct Node* rightNS;
  struct Node* parent;
} node;

bool pairCompareRatio(pair<pair<int,int>,int> i, pair<pair<int,int>,int> j) {
 return (float(i.first.first)/i.first.second)>(float(j.first.first)/j.first.second);
}

int estimate(int start, int room){

  int value=0,i=start;
  while(room>0&&i<n){
    if(Item[i].first.second<=room){
      value += Item[i].first.first;
      room -= Item[i++].first.second;
    }else{
      value += Item[i].first.first*(room/float(Item[i].first.second));
      room=0;
      i++;
    }
  }
  return value;
}

int bestSolution = 0;
node *best = NULL;


int BnB(node* &n1){
  if(n1->estimate < bestSolution){
    return n1->estimate;
  }
  if(n1->room <= 0){
    return n1->value;
  }else if( n1->depth >= n){
    if(bestSolution<n1->value){
      bestSolution = n1->value;
      best = n1;
    }
    return n1->value;
  }else{
    node *selected = (node*)malloc(sizeof(node));
    n1->leftS = selected;
    selected->selected = true;
    selected->parent = n1;
    selected->room = n1->room - Item[n1->depth].first.second;
    if(selected->room >= 0){
      selected->value = n1->value+Item[n1->depth].first.first;
      selected->depth = n1->depth+1;
      selected->estimate = selected->value + estimate(selected->depth,selected->room);
    }else{
      selected->value = n1->value;
      selected->depth = n1->depth+1;
      selected->estimate = -1;
    }

    node *notselected = (node*)malloc(sizeof(node));
    n1->rightNS = notselected;
    notselected->selected = false;
    notselected->parent = n1;
    notselected->room = n1->room;
    notselected->value = n1->value;
    notselected->depth = n1->depth+1;
    notselected->estimate = notselected->value + estimate(notselected->depth,notselected->room);

    int valS = BnB(selected);
    int valNS = BnB(notselected);
    return max(valS, valNS);
  }
}

int main(){
  cin>>n>>K;
  for(i=0;i<n;i++){
    cin>>temp_v>>temp_w;
    Item.push_back(make_pair(make_pair(temp_v,temp_w),i));
  }

  sort(Item.begin(), Item.end(), pairCompareRatio);
  node *root = (node*)malloc(sizeof(node));
  root->value = 0;
  root->room = K;
  root->depth = 0;
  root->estimate = estimate(0,root->room);
  root->selected = true;
  root->parent = NULL;
  BnB(root);
  int * X = new (nothrow) int[Item.size()];
  for(node *temp=best; temp->parent!=NULL; temp=temp->parent){
    X[Item[temp->depth-1].second] = temp->selected;
  }

  cout<<bestSolution<<" "<<0<<endl;

  cout<<endl;
    ofstream outfile;
    outfile.open("filename", ios::out);
    outfile << bestSolution << " ";
    outfile << 0 << "\n";
    for(int m=0;m<n;m++){
    	cout<<X[m]<<" ";
      outfile << X[m] << " ";
    }
  outfile.close();
  return 0;
}
