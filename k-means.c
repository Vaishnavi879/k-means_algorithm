#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
int min(float dis[20],int c)
{
    int t,min;
    min=dis[0];
    for(int i=0;i<c;i++)
    if (dis[i]<min) {min=dis[i];t=i;}
    return t;
}

struct cluster
{
    int clusterp[20][20];
};


int main() 
{
    srand (time(NULL));
    int a,m,m1,n1,n,c,c1,i,j,k,sp,z=0,sum=0,flag=0;
    float dis[50];
    int count[20][20];
    int data[20][20]={0};
    
    printf("Enter number of Data points:\n");
    scanf("%d",&m);
    
    printf("Enter number of dimensions:\n");
    scanf("%d",&n);
    
    printf("Enter data:\ndata points and their dimensional value\n");
    for(i=0;i<m;i++)
    for(j=0;j<n;j++)
    scanf("%d",&data[i][j]);
    
    printf("Enter number of clusters:\n");
    scanf("%d",&c);
    c1=c;
    
    float centroid[c][n];
    float centroid1[c][n];
    struct cluster clust[c];
    count[c][n];
    
    for(i=0;i<c;i++)
    for(j=0;j<m;j++)
    for(k=0;k<n;k++)
    clust[i].clusterp[j][k]=0;
    
    //Number of clusters equals to number of centroids
    printf("Iteration 1\n");
    printf("Centroids are:\n");
    for(i=0;i<c;i++)
    {
        int rI = rand() % m;
        for(j=0;j<n;j++)
        {
            centroid[i][j]=data[rI][j];
            printf("%0.2f ",centroid[i][j]);
        }
        printf("\n");
    }
    
    //calculating distance from one data point to all clusters and assigning to nearest cluster
    for(i=0;i<m;i++)
    {
        //for one data point
        for(j=0;j<c;j++)
        {
            //for one cluster
            sum=0;
            for(k=0;k<n;k++)
            {
                sum+=pow(centroid[j][k]-data[i][k] ,2);
            }
            dis[j]=sqrt(sum);
            printf("%f\n",dis[j]);
        }
        
        printf("%d\n",min(dis,c));
        for(k=0;k<n;k++)
        clust[min(dis,c)].clusterp[i][k]=data[i][k];
            
    }
    
    
    for(j=0;j<c1;j++)
    {
        printf("Cluster %d has following data points:\n",j+1);
        for(i=0;i<m;i++){
            for(k=0;k<n;k++){
                if(clust[j].clusterp[i][k])
                { 
                printf("%d ",clust[j].clusterp[i][k]);count[j][k]++;flag=1;}
            }
            if(flag==1)
            printf("\n");
            flag=0;
        }
    }
    
    
    //subsequent iterations
    while(z>=0)
    {
        float avg=0,flag=0;
        printf("\nIteration %d\n\n",z+2);
        printf("New centroids are:\n");
        for(i=0;i<c1;i++)
        {
            for(k=0;k<n;k++)
            {
                for(j=0;j<m;j++)
                {
                    avg+=clust[i].clusterp[j][k];
                }
                centroid1[i][k]=avg/count[i][k];
                printf("%0.3f ",centroid1[i][k]);
                avg=0;
                count[i][k]=0;
            }
            printf("\n");
        }
        printf("\n");
        
        
        //checking with previous centroid to end iterations
        for(i=0;i<c;i++){
        for(k=0;k<n;k++){
        if(centroid1[i][k]!=centroid[i][k]) {flag=1;break;}
        }if(flag==1) break;
        }
        if(i>=c) {printf("\nEnd of iterations\n");
        printf("Data points have been clustered\n");
        exit(0);}
        
        //updating the previous centroids for next iteration
        for(i=0;i<c;i++)
        for(k=0;k<n;k++)
        centroid[i][k]=centroid1[i][k];
        
        for(i=0;i<c;i++)
        for(j=0;j<m;j++)
        for(k=0;k<n;k++)
        clust[i].clusterp[j][k]=0;
        
        //calculating distance from one data point to all clusters and assigning to nearest cluster
        for(i=0;i<m;i++)
        {
            //for one data point
            for(j=0;j<c;j++)
            {
                //for one cluster
                sum=0;
                for(k=0;k<n;k++)
                {
                    sum+=pow(centroid1[j][k]-data[i][k] ,2);
                }
                dis[j]=sqrt(sum);
                printf("%f\n",dis[j]);
            }
        
            printf("%d\n",min(dis,c));
            for(k=0;k<n;k++)
            clust[min(dis,c)].clusterp[i][k]=data[i][k];
        }
        
        for(j=0;j<c1;j++)
        {
            printf("In cluster %d,following data points are classified:\n",j+1);
            for(i=0;i<m;i++){
                for(k=0;k<n;k++){
                    if(clust[j].clusterp[i][k]){ 
                    printf("%d ",clust[j].clusterp[i][k]);count[j][k]++;flag=1;}
                }
                if(flag==1)
                printf("\n");
                flag=0;
            }
        }
        z++;
    }
    
    return 0;
}
