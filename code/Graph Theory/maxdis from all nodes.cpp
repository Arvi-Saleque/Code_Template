vector<int>g[N];
 intma2[N][2];
 intmadis[N];
 intdfs1(intnode,intpar)
 {
 ma2[node][0]=ma2[node][1]=0;
 for(autoit:g[node])
 {
 if(it==par)continue;
 ma2[node][1]=max(ma2[node][1],1+dfs1(it,node));
  if(ma2[node][1]>ma2[node][0])swap(ma2[node][1],
 ma2[node][0]);
 }
 returnma2[node][0];
 }
 voiddfs2(intnode,intpar,intpre)
 {
 madis[node]=pre;
 for(autoit:g[node])
 {
 if(it==par)continue;
 madis[node]=max(madis[node],ma2[it][0]+1);
 if(ma2[node][0]==ma2[it][0]+1)dfs2(it,node,
 max(pre+1,ma2[node][1]+1));
 elsedfs2(it,node,max(pre+1,ma2[node][0]+1));
 }
 }