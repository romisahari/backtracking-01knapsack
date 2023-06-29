

//backtracking knapsack algorithm with a good way
//not today

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")

/*
w[i] : the weight of i'th object
val[i] : the value of the i'th object
obj[i] : index of the i'th valuable object
mx_val : the maximum amount of object values sum
n : the number of objects
mrk[i] : shows the state of having the object i in knapsack or not
ans[i] : shows the state of having the object i in the best knapsack or not
*/
const int maxn = 1e3 + 5;
int w[maxn], obj[maxn], val[maxn];
int mx_val = 0, n;
bool mrk[maxn], ans[maxn];

/*
input :
remaining weight,
index of the first object we haven’t decided about (to have it in Nabsack or not)
the sum of values we have from objects till now(obj[0], obj[ind - 1])

return:
checks having a chance of getting a larger sum of values if we continue this state.
we check this with greedy algorithm of knapsack and in each step we take as much as we can from the most valuable object.
*/
bool promising(int weight, int ind, int now_val){
      int indx = obj[ind];
      //obviously the object we took must be lighter than our weight.
      if(weight < 0)
            return false;
      //as we sorted the objects, the remaining objects are sorted too.
      //and the location is from ind to n in obj[n]
      for(int i = ind; (i < n) and weight; i ++){
            indx = obj[i];
            if(w[indx] <= weight){
                  //the objects are sorted. so this one is better and we will take all of it if we can.
                  now_val += val[indx];
                  weight -= w[indx];
            }
            else{
                  //if the weight is bigger, we take as much as we can.
                  now_val += ((double)weight /w[indx])* val[indx];
                  weight = 0;
            }
      }
      //if the best now_val is lower than a value sum that we made before it’s not good.
      return (now_val > mx_val);
}

/*
input :
the remaining weight of the knapsack
index of the first object we haven’t decided about (to have it in Nabsack or not)
the sum of values we have from objects untill now(obj[0], obj[ind - 1])

return:
nothing!
this is a recursive method for making a tree of decisions.
in each node decides that:
if we took the ind'th object what is the best answer for the objects (from ind'th to n’th).
and also even if we don’t take the ind'th object, what is the best answer?
the best answer for this node is the sum of:
1-the best from the 2 choices above for the remaining objects.
2-the chosen state for 0'th object to ind'th object: this value is given in input

if the answer of this node is better than any answer we have. the best answer will be updated.
*/
void knapsack(int weight, int ind, int now_val){
      if(ind < n){
            int indx = obj[ind];
            //take the object in the knapsack:
            if(w[indx] <= weight and promising(weight - w[indx], ind + 1, now_val + val[indx]) == true){
                  mrk[indx] = true;
                  knapsack(weight - w[indx], ind + 1, now_val + val[indx]);
                  mrk[indx] = false;
            }
            //didn’t take the object in the knapsack:
            if(promising(weight, ind + 1, now_val) == true){
                  knapsack(weight, ind + 1, now_val);
            }
      }
      if(mx_val < now_val){
            //updating the best answer
            for(int i = 0; i < n; i ++){
                  ans[obj[i]] = mrk[i];
            }
            mx_val = now_val;
      }
      return;
}

bool compare(int i, int j){
      /*
      for the greedy part of the algorithm
            we need the objects sorted by value/weight.
            we can get some part of an object so in each step if we take 1kg it must have the greatest value.
      this is compare function for the sort that will sort the obj in the way below:
      */
      if(((double)val[i] / w[i]) > ((double)val[j] / w[j]))
            return true;
      else
            return false;
}

int main(){
      int W;
      cout <<"give me the number of objects" <<endl;
      cin >>n;
      cout <<"give me the knapsack weight" <<endl;
      cin >>W;
      cout <<"give me the weight of each object by order of index" <<endl;
      for(int i = 0; i < n; i ++){
            cin >>w[i];
            obj[i] = i;
      }
      cout <<"give me the value of each object by order of index" <<endl;
      for(int i = 0; i < n; i ++){
            cin >>val[i];
      }
      //sorting the objects using the compare function
      sort(obj, obj + n, compare);
      //our knapsack has weight W
      //none of the object’s state has been decided so we start with obj[0]
      //because we haven’t taken any object yet, total value is 0
      knapsack(W, 0, 0);
      cout <<"the maximum total value we can have in the knapsack is: "<<mx_val <<endl;
      cout <<"objects we took: " <<endl;
      for(int i = 0; i < n; i ++){
            if(ans[i])
                  cout <<i + 1 <<' ' <<"Yes" <<endl;
            else
                  cout <<i + 1 <<' ' <<"No" <<endl;
      }
      //the end
}


