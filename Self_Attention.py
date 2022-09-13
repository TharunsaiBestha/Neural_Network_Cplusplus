import torch
class Self_attention:
    def __init__(self,m,n):
        self.Wq=torch.rand((m,n),requires_grad=True)
        self.Wk=torch.rand((m,n),requires_grad=True)
        self.Wv=torch.rand((m,n),requires_grad=True)
    def forward(self,In):
        self.Q=torch.matmul(self.Wq,In)
        self.K=torch.matmul(self.Wk,In)
        self.V=torch.matmul(self.Wv,In)
        self.T=torch.matmul(torch.transpose(self.K,0,1),self.Q)
        self.S=torch.nn.functional.softmax(self.T,dim=0)
        self.Z=torch.matmul(self.V,self.S)
        return self.Z
        