//implement convex hull graham scan algorithm

#include<bits/stdc++.h>

using namespace std;

pair<int,int> firstPoint;


int crossProduct(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3)
{
    int area = (p2.first - p1.first) * (p3.second - p1.second) - (p2.second - p1.second) * (p3.first - p1.first);
    return area;
}

int sqrDistance(pair<int,int> p1, pair<int,int> p2)  {
    int x = p1.first - p2.first;
    int y = p1.second - p2.second;
    return  x*x + y*y;
}

// sort based on angels by utilizing cross product
bool compare(pair<int,int> a, pair<int,int> b){
    // calculate the cross product of a and b
    int cross = crossProduct(firstPoint,a,b);

    // if cross product is positive then clockwise

    if(cross == 0 ){
       return (sqrDistance(firstPoint,a) < sqrDistance(firstPoint,b));   // if cross product is 0 then sort based on distance from first point
    }

    // cross > 0 clockwise else counterclockwise
    if(cross > 0){
        return true;
    }
    return false;
 
}

stack < pair<int, int > > convexHullGrahamScan(vector< pair<int, int > > &points) {
    stack< pair < int, int > > hull;
    int n = points.size();
    int min_index = 0;



    firstPoint = { points[0].first, points[0].second};

    int index = 0;
    // this has to be optimised 
    for(int i =1;i<n;i++){
        if(points[i].second < firstPoint.second){
            index = i;
           firstPoint = { points[i].first, points[i].second}; // O(n)
        }
    }

    swap(points[0], points[index]);
    //push the first point to the stack

    // sort the remaining points
    sort(points.begin()+1, points.end(),compare); // O(n log n)

    hull.push(firstPoint);
    hull.push({points[1].first, points[1].second});
    hull.push({points[2].first, points[2].second});
    for(int i =3;i<n;i++){
        pair<int,int> top = hull.top();   // O(n)
        hull.pop();

        int crossProd;
        while(!hull.empty() and crossProduct(hull.top(), top, points[i]) <= 0){
            top = hull.top();
            hull.pop();
        }

        hull.push(top);
        hull.push({points[i].first, points[i].second});
    }
    return hull; 
}

int main(){
    vector<pair<int, int > > points;//  = {(0, 3), (1, 1), (2, 2), (4, 4),(0, 0), (1, 2), (3, 1), (3, 3)};
    pair<int,int> temp;
    temp.first = 0;temp.second=3;
    points.push_back(temp);
    temp.first = 1;temp.second=1;
    points.push_back(temp);
    temp.first = 2;temp.second=2;
    points.push_back(temp);
    temp.first = 4;temp.second=4;
    points.push_back(temp);
    temp.first = 0;temp.second=0;
    points.push_back(temp);
    temp.first = 1;temp.second=2;
    points.push_back(temp);
    temp.first = 3;temp.second=1;
    points.push_back(temp);
    temp.first = 3;temp.second=3;
    points.push_back(temp);

    int n = points.size();

    stack<pair<int, int > > hull = convexHullGrahamScan(points);

        while (!hull.empty())   {
        pair<int, int > p = hull.top();
        hull.pop();

        cout<<"( "<<p.first<<" , "<<p.second<< " )"<<endl;
    }
    return 0;
}
