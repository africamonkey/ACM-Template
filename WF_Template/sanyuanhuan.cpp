#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MP make_pair
#define PB push_back
#define X first
#define Y second
#define N 100050

int deg[N],orideg[N],arr[N];
bool vis[N];
LL delta[N],cnt1[N],cnt2[N],pass3[N],pass4[N],in4[N],in3[N],out3[N],ans[N],all[N];
vector<int> e[N],orie[N];
priority_queue<pair<int,int> > q;

int main()
{
    int n,m,i,x,y,sum,root,arrs;
    pair<int,int> pa;
    vector<int>::iterator it,itr,itx;
    
    //freopen("f.in", "r", stdin);
    //freopen("f.out", "w", stdout);
    
    scanf("%d%d",&n,&m);
    for (i=1;i<=m;i++) scanf("%d%d",&x,&y),deg[x]++,deg[y]++,e[x].PB(y),e[y].PB(x);
    memcpy(orideg,deg,sizeof(orideg));
    for (i=1;i<=n;i++) orie[i]=e[i];
    for (i=1;i<=n;i++)
    {
    	sum=0;
    	for (it=e[i].begin();it!=e[i].end();it++) sum+=deg[*it]-1;
    	for (it=e[i].begin();it!=e[i].end();it++) delta[*it]+=sum-(deg[*it]-1),all[i]-=sum-(deg[*it]-1);
    }
    for (i=1;i<=n;i++)
    	for (it=e[i].begin();it!=e[i].end();it++) all[i]+=delta[*it];
    for (;!q.empty();q.pop());
    for (i=1;i<=n;i++) q.push(MP(deg[i],i));
    memset(delta,0,sizeof(delta));
    //int times=0;
    for (;!q.empty();)
    {
    	pa=q.top();
    	q.pop();
    	root=pa.Y;
    	if  (deg[root]!=pa.X||deg[root]==0) continue;
    	//times++;
    	//cerr << root << ' ' << deg[root] << endl;
    	//if  (times % 100 == 0) cerr << times << endl;
    	
    	arrs=0;
    	
    	for (itr=e[root].begin();itr!=e[root].end();itr++)
    	{
    		x=*itr;
    		if  (vis[x]) continue;
    		arr[++arrs]=x;
    		for (itx=e[x].begin();itx!=e[x].end();itx++)
    		if  (*itx!=root&&!vis[*itx])
			{
				pass4[root]+=cnt2[*itx],pass4[x]+=cnt2[*itx],pass4[*itx]+=cnt2[*itx];
				pass3[root]+=cnt1[*itx],pass3[x]+=cnt1[*itx],pass3[*itx]+=cnt1[*itx];
				delta[root]+=cnt1[*itx],out3[x]-=cnt1[*itx],out3[*itx]-=cnt1[*itx];
				delta[x]+=cnt1[*itx],out3[root]-=cnt1[*itx],out3[*itx]-=cnt1[*itx];
				delta[*itx]+=cnt1[*itx],out3[root]-=cnt1[*itx],out3[x]-=cnt1[*itx];
			}
    		for (itx=e[x].begin();itx!=e[x].end();itx++)
			if  (*itx!=root&&!vis[*itx]) cnt2[*itx]++;
			
    		cnt1[x]++;
    	}
    	
    	for (itr=e[root].begin();itr!=e[root].end();itr++)
    	{
    		x=*itr;
    		if  (vis[x]) continue;
    		for (itx=e[x].begin();itx!=e[x].end();itx++)
			if  (*itx!=root&&!vis[*itx]) cnt2[*itx]--;
			
    		cnt1[x]--;
    	}
    	
    	for (i=arrs;i>=1;i--)
    	{
    		x=arr[i];
    		for (itx=e[x].begin();itx!=e[x].end();itx++)
			if  (*itx!=root&&!vis[*itx]) pass4[x]+=cnt2[*itx];
    		for (itx=e[x].begin();itx!=e[x].end();itx++)
			if  (*itx!=root&&!vis[*itx]) cnt2[*itx]++;
    	}
    	for (i=arrs;i>=1;i--)
    	{
    		x=arr[i];
    		for (itx=e[x].begin();itx!=e[x].end();itx++)
			if  (*itx!=root&&!vis[*itx]) cnt2[*itx]--;
    	}
    	
    	for (i=1;i<=arrs;i++)
    	{
    		x=arr[i];
    		deg[x]--;
    		q.push(MP(deg[x],x));
    	}
    	deg[root]=0;
    	vis[root]=true;
    	
    }
    
    for (i=1;i<=n;i++)
    {
    	in4[i]=pass4[i];
    	in3[i]=pass3[i]*(orideg[i]-2);
    	for (it=orie[i].begin();it!=orie[i].end();it++) out3[i]+=delta[*it];
    	ans[i]=all[i]-in4[i]*2-in3[i]*2-out3[i]*2-pass3[i]*2;
    }
    for (i=1;i<=n;i++) printf("%lld\n",ans[i]);
    
    //cerr << times << endl;
    
    return 0;
}
