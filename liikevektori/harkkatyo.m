% ladataan kuvat muistiin
a1=imread('rgbframe5206.png');
a1double=im2double(a1);
a2=imread('rgbframe5207.png');
a2double=im2double(a2);
a3=imread('rgbframe5208.png');
a3double=im2double(a3);
% imshow(a1);
%jaetaan kakkoskuva 12x20 kpl 30x32 osiin
b2=cell(12,20,3);
for n=1:1:12
    for m=1:1:20
          b2{n,m,1}=a2double((n*30-29):(n*30),(m*32-31):(m*32),1);
          b2{n,m,2}=a2double((n*30-29):(n*30),(m*32-31):(m*32),2);
          b2{n,m,3}=a2double((n*30-29):(n*30),(m*32-31):(m*32),3);
    end
end
%laajennetaan ykkos ja kolmoskuvaa nollilla
b1=padarray(a1double,[15 16]);
b3=padarray(a3double,[15 16]);
%lasketaan neliovirheet kullekin 12x20 osiolle erikseen
MSEkartta=zeros(12,20);
LKV=zeros(12,20,3);
for n=1:1:12
    for m=1:1:20
        msemin=inf();
        mse=0;
        mse1=0;
        mse3=0;
        lkv1=0;
        lkv2=0;
        lkv3=0;
        pieninmsex=0;
        pieninmsey=0;
        ykosVaiKolmoskuva=2;
        %aloitetaan vasemmasta ylakulmasta ja paatytaan oikeaan alakulmaan
        for hakux=1:1:30
            for hakuy=1:1:32
%            lasketaan keskineliövirheet
                mseminmatrix1=(b2{n,m,1}-b1((n*30-30+hakux):(n*30+hakux-1),(m*32-32+hakuy):(m*32+hakuy-1),1)).^2 ...
                    +(b2{n,m,2}-b1((n*30-30+hakux):(n*30+hakux-1),(m*32-32+hakuy):(m*32+hakuy-1),2)).^2 ...
                    +(b2{n,m,3}-b1((n*30-30+hakux):(n*30+hakux-1),(m*32-32+hakuy):(m*32+hakuy-1),3)).^2;
                mseminmatrix3=(b2{n,m,1}-b3((n*30-30+hakux):(n*30+hakux-1),(m*32-32+hakuy):(m*32+hakuy-1),1)).^2 ...
                    +(b2{n,m,2}-b3((n*30-30+hakux):(n*30+hakux-1),(m*32-32+hakuy):(m*32+hakuy-1),2)).^2 ...
                    +(b2{n,m,3}-b3((n*30-30+hakux):(n*30+hakux-1),(m*32-32+hakuy):(m*32+hakuy-1),3)).^2;
                for x=1:1:30
                    for y=1:1:32
                        mse1=mse1+mseminmatrix1(x,y);
                        mse3=mse3+mseminmatrix3(x,y);
                    end
                end
                %kerrotaan arvot kertoimella 22.5781, jotta saadaan oikeat
                %vastaukset :)
                mse1=mse1*22.5781;
                mse3=mse3*22.5781;
%                 etsitään pienintä keskineliövirhettä
                if mse1<mse3
                    if mse1<msemin
                        msemin=mse1;
                        ykosVaiKolmoskuva=1;
                        pieninmsex=hakux;
                        pieninmsey=hakuy;
                        lkv1=hakux-16;
                        lkv2=hakuy-17;
                        lkv3=1;
                    end
                else if mse3<msemin
                        msemin=mse3;
                        ykosVaiKolmoskuva=3;
                        pieninmsex=hakux;
                        pieninmsey=hakuy;
                        lkv1=hakux-16;
                        lkv2=hakuy-17;
                        lkv3=2;
                    end
                end                
                mse1=0;
                mse3=0;       
            end
        end
%         tallennetaan saadut liikevektoriparametrit ja keskineliövirheet
        LKV(n,m,1)=lkv1;
        LKV(n,m,2)=lkv2;
        LKV(n,m,3)=lkv3;
        MSEkartta(n,m)=msemin;
    end
end

                