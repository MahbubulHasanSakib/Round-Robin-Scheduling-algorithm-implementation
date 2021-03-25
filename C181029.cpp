
///Name:Mahbubul Hasan

#include<bits/stdc++.h>
using namespace std;
struct job
{
    int jobNo;
    int sTime;
    int eTime;
};
bool cmp(job j1,job j2)
{
    return (j2.sTime<j2.sTime);  ///sorting the jobs in ascending order of their starting time
}

vector<job>mainV;
vector<job>vec;
vector<job>gantt;
void round_robin(int totatl_jobs,int quantum)
{
    int flag=0;
    queue<job>tempq;
    queue<job>q;
    set<int>completed;   ///it tracks the jobs served by the CPU
    tempq.push(vec[0]);
    q.push(vec[0]);
    while(!tempq.empty())
    {
        job fjob=tempq.front();  ///taking the first job from the queue to be served by the CPU
        tempq.pop();
        job pjob=q.front();
        q.pop();
        if(gantt.size()==0)  ///if no job is added to the gantt chart yet then this block will execute
        {
            if(pjob.eTime<=quantum)                        ///when burst time is not greater then time quantum
            {
                fjob.eTime=pjob.eTime+fjob.sTime;
                pjob.eTime=0;
            }
            else
            {
                fjob.eTime=quantum+fjob.sTime;        ///when burst time is greater than time quantum;
                pjob.eTime=pjob.eTime-quantum;
            }
        }
        else                                  ///when gantt chart has at least one or more jobs
        {
            job lsTime=gantt[gantt.size()-1];         /// taking the last job from gantt chart
            if(flag==1)                               ///if CPU didn't allocate any job for a time interval and then serve new one then it will execute
            {
                if(pjob.eTime<=quantum)
                {
                    fjob.eTime=pjob.eTime+fjob.sTime;
                    pjob.eTime=0;
                }
                else
                {
                    fjob.eTime=quantum+fjob.sTime;
                    pjob.eTime=pjob.eTime-quantum;
                }
                flag=0;
            }

             else if(flag==0)                    ///it will execute as usual service where  CPU is running the  jobs gradually
            {
                fjob.sTime=lsTime.eTime;
                if(pjob.eTime<=quantum)                         ///when burst time is not greater then time quantum
                {
                    fjob.eTime=pjob.eTime+lsTime.eTime;
                    pjob.eTime=0;
                }
                else
                {
                    fjob.eTime=quantum+lsTime.eTime;     ///when burst time is greater than time quantum;
                    pjob.eTime=pjob.eTime-quantum;
                }
            }
        }
        completed.insert(fjob.jobNo);
        gantt.push_back(fjob);
        job last_job=gantt[gantt.size()-1];
        for(int i=0; i<vec.size(); i++)
        {
            if(vec[i].sTime>last_job.sTime && vec[i].sTime<=last_job.eTime)   ///check if another job is present between the running time of one job
            {
                tempq.push(vec[i]);
                q.push(vec[i]);
            }
        }
        if(pjob.eTime>0)
        {
            tempq.push(pjob);
            q.push(pjob);
        }
        if(completed.size()<totatl_jobs && tempq.empty())   /// if queue is empty but some jobs are not served yet by CPU
        {
            for(int i=0; i<vec.size(); i++)
            {
                if(vec[i].sTime>last_job.eTime)           ///then the next arrival job which comes first will be added to queue
                {
                    tempq.push(vec[i]);
                    q.push(vec[i]);
                    flag=1;
                    break;
                }
            }

        }
    }
}
int main()
{
    int totatl_jobs,quantum;
    cout<<"Total number of jobs:";
    cin>>totatl_jobs;                                              ///taking total number of jobs
    int cmt[totatl_jobs+4],tat[totatl_jobs+4],wt[totatl_jobs+4];
    cout<<"Enter Arrival time and Burst time for all jobs:"<<endl;
    for(int i=0; i<totatl_jobs; i++)
    {
        job jb;
        int x,y;
        cin>>x>>y;          ///taking input of arrival time and burst time of each job
        jb.jobNo=i+1;
        jb.sTime=x;
        jb.eTime=y;
        vec.push_back(jb);  ///storing each job to a vector with its job no,arrival time and burst time
        mainV.push_back(jb);
    }
    cout<<"Enter quantum size:";
    cin>>quantum;
    sort(vec.begin(),vec.end(),cmp); ///sorting each job in ascending order of their arrival time at first
    round_robin(totatl_jobs,quantum);
    for(int i=1; i<=totatl_jobs; i++)
    {
        for(int j=gantt.size()-1; j>=0; j--)
        {
            if(gantt[j].jobNo==i)
            {
                cmt[i]=gantt[j].eTime;  ///taking the last ending time of a job as it's completion time from gantt chart
                break;
            }
        }
    }
    for(int i=1; i<=totatl_jobs; i++)
    {
        tat[i]=cmt[i]-mainV[i-1].sTime;    ///calculating turn around time of each job
        wt[i]=tat[i]-mainV[i-1].eTime;     ///calculating waiting time of each job
    }
    cout<<" Jobs    "<<"     "<<"Arrival Time"<<"   "<<"Burst Time"<<"      "<<"Completion Time"<<"     "<<"Turn around Time"<<"      "<<"Waiting Time"<<"   "<<endl;
    int totatl_tat=0,totatl_wt=0;
    for(int i=1; i<=totatl_jobs; i++)
    {
        totatl_tat=totatl_tat+tat[i];    ///total turn around time
        totatl_wt=totatl_wt+wt[i];       ///total waiting time
        cout<<"  "<<i<<"\t\t  "<<mainV[i-1].sTime<<"\t\t"<<mainV[i-1].eTime<<"\t\t  "<<cmt[i]<<"\t\t\t"<<tat[i]<<"\t\t   "<<wt[i]<<"   "<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<"Average Turn around Time is:"<<(totatl_tat/(float)totatl_jobs)<<endl;   ///showing average turn around time
    cout<<"Average Waiting Time is:"<<(totatl_wt/(float)totatl_jobs)<<endl;       ///showing average waiting time
    return 0;
}
