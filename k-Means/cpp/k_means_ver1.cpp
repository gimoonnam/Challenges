//
//  myTrial.cpp
//  kMeansPractice
//
//  Created by Gimoon Nam on 3/23/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <cmath>
#define SQR(X)((X)*(X))

using namespace std;


void getNearestCluster(const int K, const int n_points,
					   vector<int>&labels,vector<vector<double>>&all_points, vector<vector<double>>&centroid){
	
	for (int i=0; i<n_points;i++)
	{
		double min_dis = sqrt(SQR(all_points[i][0]-centroid[labels[i]][0])
							  +SQR(all_points[i][1]-centroid[labels[i]][1]));
		for (int k=0; k<K; k++)
		{
			double dis = sqrt(SQR(all_points[i][0]-centroid[k][0])
							  +SQR(all_points[i][1]-centroid[k][1]));
			if(dis < min_dis){
				min_dis = dis;
				labels[i]=k;
			}
		}
	}
	
}


void updateCentroid(const int K, const int n_points,vector<int>&labels,
					vector<vector<double>>&all_points,vector<vector<double>>&centroid){
	
	// update centroid
	vector<int> count;
	
	for(int k=0; k<K; k++){
		centroid[k][0] =0;
		centroid[k][1] =0;
		count.push_back(0);
	}
	
	for(int i=0; i<n_points;i++){
		centroid[labels[i]][0] += all_points[i][0];
		centroid[labels[i]][1] += all_points[i][1];
		count[labels[i]]++;
	}
	
	for(int k=0; k<K;k++){
		if (count[k]!=0){
			centroid[k][0] /=(double)count[k];
			centroid[k][1] /=(double)count[k];
		}
		cout << k << ": " << centroid[k][0] << " " << centroid[k][1] << endl;
	}
	
}

void print_points(const int n_points, vector<vector<double>>&all_points, vector<int>&labels){
	for(int i=0;i<n_points;i++){
		cout << all_points[i][0] << " " << all_points[i][1] << ": "<< labels[i] << endl;
	}
}


int main(){
    //Open file for fetching points
    string filename = "input.txt";
    ifstream infile(filename.c_str());
	
    if(!infile.is_open()){
        cout<<"Error: Failed to open file."<<endl;
        return 1;
    }
	vector<vector<double>> all_points;
	string line;

	while(getline(infile,line)){
		stringstream is(line);
		double val;
		vector<double> points;
		while(is >> val){
			points.push_back(val);
		}
		all_points.push_back(points);

	}
	const int n_points = (int)all_points.size();
	
	cout << "data are fetched successfully!!" << endl;
	
		
	// initial cluster
	int K= 3;
	vector<int> clusters;
	vector<vector<double>> centroid;
	
	vector<int> labels;
	for(int i=0;i<n_points;i++){
		labels.push_back((int)rand()%K);
	}

	for (int i=0;i<K ;i++){
		int idx = (int)rand()%K;
		clusters.push_back(idx);
		centroid.push_back({all_points[idx][0],all_points[idx][1]});
	}
		
	
	vector<vector<double>> centroid_prev={{0,0},{0,0},{0,0}};
	int Iter=0;
	int counter=0;
	

	while(counter <= 3 || Iter > 100){
		// get the nearest cluster for all points ...
		getNearestCluster(K, n_points, labels, all_points, centroid);
		// update centroid
		updateCentroid(K, n_points, labels, all_points, centroid);
		// print results
		print_points(n_points, all_points, labels);
		
		if (centroid == centroid_prev){
			counter++;
		}
		else {
			centroid_prev = centroid;
			counter=0;
		}
		
		Iter++;
	}
	
	
	
	return 0;
}
