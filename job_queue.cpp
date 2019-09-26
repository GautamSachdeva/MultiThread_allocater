#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  struct node{
  	int worker;
  	int time;
  };typedef struct node node;
  vector<node> data_;
  
  vector<int> assigned_workers_;
  vector<long long> start_times_;
   	
  void sift_down(int i){
  	int min_index= i;
  	int l = 2*i + 1;
  	if(l <= (data_.size() - 1) && data_[l].time < data_[min_index].time){
  		min_index = l;
	  }
	int r = 2*i + 2;
	if( r <= data_.size() - 1 && data_[r].time < data_[min_index].time){
		min_index = r;
	}
	if(min_index != i){
		swap(data_[i],data_[min_index]);
		sift_down(min_index);
	}
  }
  
  void heapify(){
  	int last_index = data_.size() - 1;
	int n = (last_index-1)/2;
	for(int i = n ; i >= 0 ; i--){
		sift_down(i);
  	}
  }
		
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm
    int next_job = 0;
    for(int i = 0 ; i < num_workers_ ; i++){
    	if(jobs_.size()>i){
    		assigned_workers_.push_back(i);
    		start_times_.push_back(0);
    		node w;
    		w.worker = i;
    		w.time = jobs_[i];
    		data_.push_back(w);
		}
	}
	if(num_workers_ >= jobs_.size()){
		return;
	}
	heapify();
	int counter = 0;
	for(int i = num_workers_ ; i < jobs_.size() ; i++ ){
		assigned_workers_.push_back(data_[0].worker);
		start_times_.push_back(0);
		data_[0].time = jobs_[i];
		sift_down(0);
	}
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
