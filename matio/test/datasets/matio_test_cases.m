% Generate test datasets for matio library
%
% Copyright 2010-2013 Christopher C. Hulbert. All rights reserved.
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
%
%    1. Redistributions of source code must retain the above copyright notice,
%       this list of conditions and the following disclaimer.
%
%    2. Redistributions in binary form must reproduce the above copyright
%       notice, this list of conditions and the following disclaimer in the
%       documentation and/or other materials provided with the distribution.
%
% THIS SOFTWARE IS PROVIDED BY CHRISTOPHER C. HULBERT ``AS IS'' AND ANY EXPRESS
% OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
% OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
% EVENT SHALL CHRISTOPHER C. HULBERT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
% INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
% (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
% LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
% ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
% (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
% SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

[c,m,e]=computer;
if e == 'B'
  e_str = '_be';
else
  e_str = '_le';
end
rand('seed',931316785);

var1 = reshape(1:20,4,5);
var2 = reshape(single(1:20),4,5);
var3 = reshape(int64(1:20),4,5);
var4 = reshape(uint64(1:20),4,5);
var5 = reshape(int32(1:20),4,5);
var6 = reshape(uint32(1:20),4,5);
var7 = reshape(int16(1:20),4,5);
var8 = reshape(uint16(1:20),4,5);
var9 = reshape(int8(1:20),4,5);
var10 = reshape(uint8(1:20),4,5);
var11 = reshape(complex(1:20,21:40),4,5);
var12 = reshape(single(complex(1:20,21:40)),4,5);
var13 = reshape(int64(complex(1:20,21:40)),4,5);
var14 = reshape(uint64(complex(1:20,21:40)),4,5);
var15 = reshape(int32(complex(1:20,21:40)),4,5);
var16 = reshape(uint32(complex(1:20,21:40)),4,5);
var17 = reshape(int16(complex(1:20,21:40)),4,5);
var18 = reshape(uint16(complex(1:20,21:40)),4,5);
var19 = reshape(int8(complex(1:20,21:40)),4,5);
var20 = reshape(uint8(complex(1:20,21:40)),4,5);
var21 = sparse(diag(1:5));
var22 = sparse(diag(complex(1:5,6:10)));
var23 = [];
var24 = ['abcdefghijklmnopqrstuvwxyz';
         'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
         '1234567890!@#$%^&*()-_=+`~';
         '[{]}\|;:''",<.>/?          '];

%% Structure Variables
var25 = struct();
var26 = repmat(struct('field1',[],'field2',[]),0,1);
var27(1).field1 = zeros(0,1);
var27(1).field2 = repmat(' ',0,1);
var27(2).field1 = repmat(struct,0,1);
var27(2).field2 = repmat({zeros(0,0)},0,1);
var28 = [struct('field1',1,'field2',reshape(2:13,3,4));
         struct('field1',14,'field2',reshape(15:26,3,4))];
var29 = [struct('field1',single(1),'field2',reshape(single(2:13),3,4));
         struct('field1',single(14),'field2',reshape(single(15:26),3,4))];
var30 = [struct('field1',int64(1),'field2',reshape(int64(2:13),3,4));
         struct('field1',int64(14),'field2',reshape(int64(15:26),3,4))];
var31 = [struct('field1',uint64(1),'field2',reshape(uint64(2:13),3,4));
         struct('field1',uint64(14),'field2',reshape(uint64(15:26),3,4))];
var32 = [struct('field1',int32(1),'field2',reshape(int32(2:13),3,4));
         struct('field1',int32(14),'field2',reshape(int32(15:26),3,4))];
var33 = [struct('field1',uint32(1),'field2',reshape(uint32(2:13),3,4));
         struct('field1',uint32(14),'field2',reshape(uint32(15:26),3,4))];
var34 = [struct('field1',int16(1),'field2',reshape(int16(2:13),3,4));
         struct('field1',int16(14),'field2',reshape(int16(15:26),3,4))];
var35 = [struct('field1',uint16(1),'field2',reshape(uint16(2:13),3,4));
         struct('field1',uint16(14),'field2',reshape(uint16(15:26),3,4))];
var36 = [struct('field1',int8(1),'field2',reshape(int8(2:13),3,4));
         struct('field1',int8(14),'field2',reshape(int8(15:26),3,4))];
var37 = [struct('field1',uint8(1),'field2',reshape(uint8(2:13),3,4));
         struct('field1',uint8(14),'field2',reshape(uint8(15:26),3,4))];
var38 = [struct('field1',1+51*j,'field2',reshape((2:13)+(52:63)*j,3,4));
         struct('field1',14+64*j,'field2',reshape((15:26)+(65:76)*j,3,4))];
var39 = [struct('field1',single(1+51*j),...
                'field2',reshape(single((2:13)+(52:63)*j),3,4));
         struct('field1',single(14+64*j),...
                'field2',reshape(single((15:26)+(65:76)*j),3,4))];
var40 = [struct('field1',int64(1+51*j),...
                'field2',reshape(int64((2:13)+(52:63)*j),3,4));
         struct('field1',int64(14+64*j),...
                'field2',reshape(int64((15:26)+(65:76)*j),3,4))];
var41 = [struct('field1',uint64(1+51*j),...
                'field2',reshape(uint64((2:13)+(52:63)*j),3,4));
         struct('field1',uint64(14+64*j),...
                'field2',reshape(uint64((15:26)+(65:76)*j),3,4))];
var42 = [struct('field1',int32(1+51*j),...
                'field2',reshape(int32((2:13)+(52:63)*j),3,4));
         struct('field1',int32(14+64*j),...
                'field2',reshape(int32((15:26)+(65:76)*j),3,4))];
var43 = [struct('field1',uint32(1+51*j),...
                'field2',reshape(uint32((2:13)+(52:63)*j),3,4));
         struct('field1',uint32(14+64*j),...
                'field2',reshape(uint32((15:26)+(65:76)*j),3,4))];
var44 = [struct('field1',int16(1+51*j),...
                'field2',reshape(int16((2:13)+(52:63)*j),3,4));
         struct('field1',int16(14+64*j),...
                'field2',reshape(int16((15:26)+(65:76)*j),3,4))];
var45 = [struct('field1',uint16(1+51*j),...
                'field2',reshape(uint16((2:13)+(52:63)*j),3,4));
         struct('field1',uint16(14+64*j),...
                'field2',reshape(uint16((15:26)+(65:76)*j),3,4))];
var46 = [struct('field1',int8(1+51*j),...
                'field2',reshape(int8((2:13)+(52:63)*j),3,4));
         struct('field1',int8(14+64*j),...
                'field2',reshape(int8((15:26)+(65:76)*j),3,4))];
var47 = [struct('field1',uint8(1+51*j),...
                'field2',reshape(uint8((2:13)+(52:63)*j),3,4));
         struct('field1',uint8(14+64*j),...
                'field2',reshape(uint8((15:26)+(65:76)*j),3,4))];
var48 = struct('field1',sparse(triu(reshape(1:20,4,5))),...
               'field2',sparse(triu(reshape(1:20,4,5))'));
var49 = struct('field1',sparse(triu(reshape((1:20)+j*(21:40),4,5))),...
               'field2',sparse(triu(reshape((1:20)+j*(21:40),4,5))'));
var50 = [struct('field1','abcdefghijklmnopqrstuvwxyz',...;
                'field2','ABCDEFGHIJKLMNOPQRSTUVWXYZ');
         struct('field1','1234567890!@#$%^&*()-_=+`~',...
                'field2','[{]}\|;:''",<.>/?          ')];

%% Cell-Array Variables
var51 = {};
var52 = {[] single([]) int64([]) uint64([]) int32([]) uint32([]) int16([]) uint16([]) int8([]) uint8([])};
var53 = {[1 2;3 4] [5 6 7;8 9 10] [11 12 13 14;15 16 17 18];
         [19 20;21 22] [23 24;25 26;27 28] [29 30;31 32;33 34;35 36]};
var54 = {single([1 2;3 4]) single([5 6 7;8 9 10]) ...
         single([11 12 13 14;15 16 17 18]); single([19 20;21 22]) ...
         single([23 24;25 26;27 28]) single([29 30;31 32;33 34;35 36])};
var55 = {int64([1 2;3 4]) int64([5 6 7;8 9 10]) ...
         int64([11 12 13 14;15 16 17 18]); int64([19 20;21 22]) ...
         int64([23 24;25 26;27 28]) int64([29 30;31 32;33 34;35 36])};
var56 = {uint64([1 2;3 4]) uint64([5 6 7;8 9 10]) ...
         uint64([11 12 13 14;15 16 17 18]); uint64([19 20;21 22]) ...
         uint64([23 24;25 26;27 28]) uint64([29 30;31 32;33 34;35 36])};
var57 = {int32([1 2;3 4]) int32([5 6 7;8 9 10]) ...
         int32([11 12 13 14;15 16 17 18]); int32([19 20;21 22]) ...
         int32([23 24;25 26;27 28]) int32([29 30;31 32;33 34;35 36])};
var58 = {uint32([1 2;3 4]) uint32([5 6 7;8 9 10]) ...
         uint32([11 12 13 14;15 16 17 18]); uint32([19 20;21 22]) ...
         uint32([23 24;25 26;27 28]) uint32([29 30;31 32;33 34;35 36])};
var59 = {int16([1 2;3 4]) int16([5 6 7;8 9 10]) ...
         int16([11 12 13 14;15 16 17 18]); int16([19 20;21 22]) ...
         int16([23 24;25 26;27 28]) int16([29 30;31 32;33 34;35 36])};
var60 = {uint16([1 2;3 4]) uint16([5 6 7;8 9 10]) ...
         uint16([11 12 13 14;15 16 17 18]); uint16([19 20;21 22]) ...
         uint16([23 24;25 26;27 28]) uint16([29 30;31 32;33 34;35 36])};
var61 = {int8([1 2;3 4]) int8([5 6 7;8 9 10]) ...
         int8([11 12 13 14;15 16 17 18]); int8([19 20;21 22]) ...
         int8([23 24;25 26;27 28]) int8([29 30;31 32;33 34;35 36])};
var62 = {uint8([1 2;3 4]) uint8([5 6 7;8 9 10]) ...
         uint8([11 12 13 14;15 16 17 18]); uint8([19 20;21 22]) ...
         uint8([23 24;25 26;27 28]) uint8([29 30;31 32;33 34;35 36])};
var63 = {sparse(triu(reshape(1:20,4,5))) sparse(triu(reshape(1:20,4,5))')};
var64 = {sparse(triu(reshape((1:20)+j*(21:40),4,5)));
         sparse(triu(reshape((1:20)+j*(21:40),4,5))')};
var65 = {'abcdefghijklmnopqrstuvwxyz' '1234567890!@#$%^&*()-_=+`~';
         'ABCDEFGHIJKLMNOPQRSTUVWXYZ' '[{]}\|;:''",<.>/?          '};
var66 = {var25 var26 var27};
var67 = {var28 var29 var30 var31 var32 var33 var34 var35 var36 var37;
         var38 var39 var40 var41 var42 var43 var44 var45 var46 var47};
var68 = {struct('field1',sparse(triu(reshape(1:20,4,5))),...
                'field2',sparse(triu(reshape(1:20,4,5))'));
         struct('field1',sparse(triu(reshape((1:20)+j*(21:40),4,5))),...
                'field2',sparse(triu(reshape((1:20)+j*(21:40),4,5))'))};
var69 = {struct('field1','abcdefghijklmnopqrstuvwxyz',...;
                'field2','ABCDEFGHIJKLMNOPQRSTUVWXYZ');
         struct('field1','1234567890!@#$%^&*()-_=+`~',...
                'field2','[{]}\|;:''",<.>/?          ')};

int16_data = intmin('int16'):intmax('int16');
uint16_data = intmin('uint16'):intmax('uint16');
int8_data = int8(-128:127);
uint8_data = uint8(0:255);
var70 = reshape(1:32*32*32,32,32,32);
var71 = reshape(single(1:32*32*32),32,32,32);
var72 = reshape(int64(1:32*32*32),32,32,32);
var73 = reshape(uint64(1:32*32*32),32,32,32);
var74 = reshape(int32(1:32*32*32),32,32,32);
var75 = reshape(uint32(1:32*32*32),32,32,32);
var76 = reshape(int16(1:32*32*32),32,32,32);
var77 = reshape(uint16(1:32*32*32),32,32,32);
I = round(1+(numel(int8_data)-1)*rand(32,32,32));
J = round(1+(numel(int8_data)-1)*rand(32,32,32));
var78 = reshape(int8_data(I),32,32,32);
I = round(1+(numel(uint8_data)-1)*rand(32,32,32));
J = round(1+(numel(uint8_data)-1)*rand(32,32,32));
var79 = reshape(uint8_data(I),32,32,32);
var80 = reshape((1:2:2*32^3) + j*(2:2:2*32^3),32,32,32);
var81 = reshape(single((1:2:2*32^3) + j*(2:2:2*32^3)),32,32,32);
var82 = reshape(int64((1:2:2*32^3) + j*(2:2:2*32^3)),32,32,32);
var83 = reshape(uint64((1:2:2*32^3) + j*(2:2:2*32^3)),32,32,32);
var84 = reshape(int32((1:2:2*32^3) + j*(2:2:2*32^3)),32,32,32);
var85 = reshape(uint32((1:2:2*32^3) + j*(2:2:2*32^3)),32,32,32);
I = round(1+(numel(int16_data)-1)*rand(32,32,32));
J = round(1+(numel(int16_data)-1)*rand(32,32,32));
var86 = reshape(complex(int16_data(I),int16_data(J)),32,32,32);
I = round(1+(numel(uint16_data)-1)*rand(32,32,32));
J = round(1+(numel(uint16_data)-1)*rand(32,32,32));
var87 = reshape(complex(uint16_data(I),uint16_data(J)),32,32,32);
I = round(1+(numel(int8_data)-1)*rand(32,32,32));
J = round(1+(numel(int8_data)-1)*rand(32,32,32));
var88 = reshape(complex(int8_data(I),int8_data(J)),32,32,32);
I = round(1+(numel(uint8_data)-1)*rand(32,32,32));
J = round(1+(numel(uint8_data)-1)*rand(32,32,32));
var89 = reshape(complex(uint8_data(I),uint8_data(J)),32,32,32);

var90 = tril(true(5));
var91 = [struct('field1',logical(mod(reshape(0:19,4,5),2)),...
                'field2',~mod(reshape(0:19,4,5),2));...
         struct('field1',tril(true(5)),'field2',triu(true(5)))];
var92 = {logical(mod(reshape(0:19,4,5),2));~mod(reshape(0:19,4,5),2);...
        tril(true(5));triu(true(5))};

save('-v6',['matio_test_cases_uncompressed' e_str '.mat'],'var*');
save(['matio_test_cases_compressed' e_str '.mat'],'var*');
save('-v7.3',['matio_test_cases_hdf' e_str '.mat'],'var*');
save('-v4',['matio_test_cases_v4' e_str '.mat'],'var1','var11','var21',...
     'var22','var24');

x = pi;
save('-v4',['small_v4' e_str '.mat'],'x');
