#include <iostream>
using namespace std;

struct prcss{
    int priority;
    int bst_t;
    int tt_time;
    int t_t=0;
};

struct queue{
    int priority_start;
    int priority_end;
    int t_t=0;
    int length = 0;
    prcss *p;
    bool executed = false;
};

bool Incomplete(queue q[]){
    bool a=false;
    int countInc=0;
        for(int i=0;i<3;i++){
                countInc=0;
            for(int j=0;j<q[i].length;j++){
                if(q[i].p[j].bst_t != 0){
                    a=true;
                }
                else{
                    countInc+=1;
                }
            }
            if(countInc==q[i].length){

                q[i].executed = true;
            }
        }
        return a;
}



void sort_prcss(queue q){

    for(int i=1;i<q.length;i++){
        for(int j=0;j<q.length-1;j++){
            if(q.p[j].priority<q.p[j+1].priority){
                prcss temp = q.p[j+1];
                q.p[j+1] = q.p[j];
                q.p[j] = temp;
            }
        }
    }
}


void Complete_t(queue q[]){
    bool a = Incomplete(q);
    for(int i=0;i<3;i++){
        if(q[i].executed==false){
            for(int j=0;j<q[i].length;j++){
                if(q[i].p[j].bst_t!=0){
                    q[i].p[j].t_t+=1;
                }
            }
            q[i].t_t+=1;
        }
    }
}

main(){
    queue q[3];
    q[0].priority_start = 12;
    q[0].priority_end = 6;
    q[1].priority_start = 14;
    q[1].priority_end = 8;
    q[2].priority_start = 3;
    q[2].priority_end = 7;

    int no_of_prcsses,priority_of_prcss,bst_t_of_prcss;
    //Prompt User for entering Prcsses and assigning it to respective queue.
    cout<<"Enter the number of process to be executed\n";
    cin>>no_of_prcsses;
    prcss p1[no_of_prcsses];

    for(int i=0;i<no_of_prcsses;i++){
        cout<<"Enter the priority of the process\n";
        cin>>priority_of_prcss;
        cout<<"Enter the burst time of the process\n";
        cin>>bst_t_of_prcss;
        p1[i].priority = priority_of_prcss;
        p1[i].bst_t = bst_t_of_prcss;
        p1[i].tt_time = bst_t_of_prcss;
        for(int j=0;j<3;j++){
        if(q[j].priority_start<=priority_of_prcss && priority_of_prcss<=q[j].priority_end){
            q[j].length++;
        }
        }
    }

    for(int i =0;i<3;i++){
        int len = q[i].length;
        q[i].p = new prcss[len];
    }


    int a=0;
    int b=0;
    int c=0;

    for(int i =0;i<3;i++){
        for(int j=0;j<no_of_prcsses;j++){
            if((q[i].priority_start<=p1[j].priority) && (p1[j].priority<=q[i].priority_end)){
                if(i==0)
                {
                    q[i].p[a++] = p1[j];

                    }
                else if(i==1){
                    q[i].p[b++] = p1[j];
                    }
                else{
                    q[i].p[c++] = p1[j];
                    }
            }
        }
    }

    a--;b--;c--;
    for(int i=0;i<3;i++){
        cout<<"Queue "<<i+1<<" : \t";
        for(int j=0;j<q[i].length;j++){
            cout<<q[i].p[j].priority<<"->";
        }
        cout<<"NULL\n";
    }


    //While RR on multiple queue is not complete, keep on repeating
    int timer = 0;
    int l =-1;
    int rr_timer = 6;
    int counter=0;
    int counterps=0;
    int counterfcfs=0;
    while(Incomplete(q)){
        if(timer == 10){
            timer = 0;
        }
        l+=1;
        if(l>=3){
            l=l%3;
        }

        //Prcss lth queue if its already not executed
        //If its executed change the value of l
        if(q[l].executed == true){
                cout<<"Queue "<<l+1<<" completed\n";
            l+=1;
            if(l>=3){
                l=l%3;
            }
            continue;
        }
        if(l==0){
            cout<<"Queue "<<l+1<<" in hand\n";
            if(rr_timer == 0){
                rr_timer = 6;
            }

            for(int i=0;i<q[l].length;i++){
                if(q[l].p[i].bst_t==0){
                    counter++;
                    continue;
                }
                if(counter == q[l].length){
                    break;
                }
                while(rr_timer>0 && q[l].p[i].bst_t!=0 && timer!=10){
                    cout<<"Executing queue 1 and "<<i+1<<" prcss for a unit time. Prcocess has priority of "<<q[l].p[i].priority<<"\n";
                    q[l].p[i].bst_t--;
                    Complete_t(q);
                    rr_timer--;
                    timer++;

                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].bst_t==0 && rr_timer ==0){
                    rr_timer = 6;
                    if(i == (q[i].length-1)){
                        i=-1;
                    }
                    continue;
                }
                if(q[l].p[i].bst_t==0 && rr_timer > 0){
                    if(i == (q[i].length-1)){
                        i=-1;
                    }
                    continue;
                }
                if(rr_timer <= 0){
                    rr_timer = 6;
                    if(i == (q[i].length-1)){
                        i=-1;
                    }
                    continue;
                }

            }
        }


        else if(l==1){
            cout<<"Queue "<<l+1<<" in hand\n";
            sort_prcss(q[l]);
            for(int i=0;i<q[l].length;i++){
                if(q[l].p[i].bst_t==0){
                    counterps++;
                    continue;
                }
                if(counterps == q[l].length){
                    break;
                }
                while(q[l].p[i].bst_t!=0 && timer!=10){
                    cout<<"Executing queue 2 and "<<i+1<<" process for a unit time. Prcss has priority of "<<q[l].p[i].priority<<"\n";
                    q[l].p[i].bst_t--;
                    Complete_t(q);
                    timer++;

                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].bst_t==0){
                        continue;
                }

            }
        }
        else{
            cout<<"Queue "<<l+1<<" in hand\n";
            for(int i=0;i<q[l].length;i++){
                if(q[l].p[i].bst_t==0){
                    counterfcfs++;
                    continue;
                }
                if(counterfcfs == q[l].length){
                    break;
                }
                while(q[l].p[i].bst_t!=0 && timer!=10){
                    cout<<"Executing queue 3 and "<<i+1<<" prcss for a unit time. Prcss has priority of "<<q[l].p[i].priority<<"\n";
                    q[l].p[i].bst_t--;
                    Complete_t(q);

                    timer++;
                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].bst_t==0){
                        continue;
                }

            }

        }
        cout<<"Broke from queue "<<l+1<<"\n";
    }

    for(int i=0;i<3;i++){
            cout<<"\nTime taken for queue "<<i+1<<" to execute: "<<q[i].t_t<<"\n";
        for(int j=0;j<q[i].length;j++){
            cout<<"Process "<<j+1<<" of queue "<<i+1<<" took "<<q[i].p[j].t_t<<"\n";
        }
    }

    int sum_tt=0;
    int sum_wt=0;

    cout<<"\n\nProcess   ====>  Turn Around Time and Waiting Time\n";
    for(int i=0;i<3;i++){
            cout<<"Queue "<<i+1<<"\n";
        for(int j=0;j<q[i].length;j++){
            cout<<"Process P"<<j+1<<"\t"<<q[i].p[j].t_t<<"\t\t    "<<q[i].p[j].t_t-q[i].p[j].tt_time<<"\n";
            sum_tt+=q[i].p[j].t_t;
            sum_wt+=q[i].p[j].t_t-q[i].p[j].tt_time;
        }
    }

    cout<<"\n The average turnaround time is : "<<sum_tt/no_of_prcsses<<endl;
    cout<<"\n The average waiting time is : "<<sum_wt/no_of_prcsses<<endl;

}
