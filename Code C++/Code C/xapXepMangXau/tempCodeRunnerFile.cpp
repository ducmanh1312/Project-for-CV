    vector<int> A = arr;
    
    int n =(int) A.size(), k = (n-1)/2;
    vector<int> B,C;
    for(int i = 0; i < k; i++) B.push_back(A[i]);
    for(int i = k; i < n; i++) C.push_back(A[i]);

    if(B.size() > 1) B = sortArray(B);
    if(C.size() > 1) C = sortArray(C);

    A.clear();
    A.resize(B.size + C.size());

    merge(B.begin(),B.end(),C.begin(),C.end(),A.begin());

    return A;