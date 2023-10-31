#include <stdio.h>
#include <stdlib.h>

int calcoloMCD(int,int);
void graphic(int, int);
void print(int, int, int);

int main() {

    int GoStop = 0;

    do {
        int numeroCongruenze, verificaCondizioni = 0, mcd, contatore = 0;

        printf("\n  Inserire il numero di congruenze del sistema: ");
        scanf("%d", &numeroCongruenze);

        while (numeroCongruenze < 2) {

          printf("  Minimo 2 congruenze, riprovare: ");
          scanf("%d", &numeroCongruenze);
        }

        printf("\n");

        int Sistema[numeroCongruenze][3];

        for (int i=0; i<numeroCongruenze; i++) {

            printf("  Congruenza %d: inserire A, B e MOD separati dallo spazio o dall'invio: ",i+1);
            scanf("%d %d %d", &Sistema[i][0], &Sistema[i][1], &Sistema[i][2]);
        }

        printf("\n  Il sistema dato e' il seguente:\n\n  /\n");

        for (int i=0; i<numeroCongruenze; i++) {

                graphic(numeroCongruenze, i);
                print(Sistema[i][0], Sistema[i][1], Sistema[i][2]);
        }

        printf("  \\\n"); //fine traccia - inizio svolgimento

        for (int i=0; i<numeroCongruenze; i++) {

                mcd = calcoloMCD(Sistema[i][0], Sistema[i][2]);

                if (mcd != 1 && Sistema[i][1]%mcd == 0) { //dividiamo per il MCD

                    Sistema[i][0]/=mcd;
                    Sistema[i][1]/=mcd;
                    Sistema[i][2]/=mcd;
                    contatore++;
                }
        }

        if (contatore != 0) {

            printf("\n  Le soluzioni in Z del sistema dato sono le stesse del sistema:\n\n  /\n");

            for (int i=0; i<numeroCongruenze; i++) {

                graphic(numeroCongruenze, i);
                print(Sistema[i][0], Sistema[i][1], Sistema[i][2]);
            }

            printf("  \\\n");
        }

        for (int i=0; i<numeroCongruenze; i++) {

                for (int j=i+1; j<numeroCongruenze && verificaCondizioni == 0; j++) {

                    mcd = calcoloMCD(Sistema[i][2], Sistema[j][2]);

                    printf("\n  MCD(%d,%d) = %d.", Sistema[i][2], Sistema[j][2], mcd);

                    if (mcd != 1) {//primo controllo (MCD dei moduli a due a due deve valere 1)
                        verificaCondizioni = -1;
                        printf("\n\n  Il sistema non ammette soluzione perche' l'MCD fra %d e %d non vale 1.\n", Sistema[i][2], Sistema[j][2]);
                    }
                }
        }

        if (verificaCondizioni == 0) {

            printf("\n\n  Il sistema potrebbe ammettere soluzione.\n");

            for (int i=0; i<numeroCongruenze && verificaCondizioni == 0; i++) {

                mcd = calcoloMCD(Sistema[i][0], Sistema[i][2]);
                printf("\n  MCD(%d,%d) = %d", Sistema[i][0], Sistema[i][2], mcd);

                if (mcd != 1) {
                    printf(" che non divide %d. Questa congruenza non ammette soluzione --> il sistema non ammette soluzione.\n", Sistema[i][1]);
                    verificaCondizioni = -1;
                }
                else
                    printf(" che divide %d.", Sistema[i][1]);
            }
        }
        if (verificaCondizioni == 0) {

            printf("\n\n  Tutte e %d le congruenze ammettono soluzione --> il sistema ammette soluzione.\n  Riscriviamolo", numeroCongruenze);

            int R = 1, X = 0;
            contatore = 0;
            int Rn[numeroCongruenze], Xn[numeroCongruenze];

            for (int i=0; i<numeroCongruenze; i++)
                if (Sistema[i][0] == 1)
                    contatore++;

            if (contatore == numeroCongruenze)
                printf(":\n\n  /\n");
            else
                printf(" con tutti i coefficenti della x con valore 1:\n\n  /\n");

            for (int i=0; i<numeroCongruenze; i++) {

                if (Sistema[i][0] != 1) {

                    int k = 0;
                    while((k*Sistema[i][0] - Sistema[i][1]) % Sistema[i][2] != 0) k++;
                    Sistema[i][1] = k;
                }

                Sistema[i][0] = 1;

                graphic(numeroCongruenze, i);
                printf("| x congruo a %d mod %d\n", Sistema[i][1], Sistema[i][2]);

                R*=Sistema[i][2];
            }

            printf("  \\\n\n  Applicazione del teorema cinese del resto, R = ");
            for (int i=0; i<numeroCongruenze-1; i++) printf("%d*", Sistema[i][2]);
            printf("%d = %d.\n\n", Sistema[numeroCongruenze-1][2], R);

            for (int i=0; i<numeroCongruenze; i++) {

                Rn[i] = R/Sistema[i][2];
                printf("  R%d = %d/%d = %d.\n", i+1, R, Sistema[i][2], Rn[i]);
                Sistema[i][0] = Rn[i];
            }

            printf("\n  Si considerino ora le seguenti congruenze:\n\n");
            for (int i=0; i<numeroCongruenze; i++) printf("  %d) %dx congruo a %d mod %d.\n", i+1, Sistema[i][0], Sistema[i][1], Sistema[i][2]);

            for (int i=0; i<numeroCongruenze; i++) {

                int k = 0;
                while((k*Sistema[i][0] - Sistema[i][1]) % Sistema[i][2] != 0) k++;
                Xn[i] = k;
                printf("\n  %d) ha come soluzione %d, che sara' chiamata X%d.",i+1, Xn[i],i+1);
            }

            printf("\n\n  Sia X =");

            for (int i=0; i<numeroCongruenze-1; i++) printf(" R%dX%d +",i+1,i+1);
            printf(" R%dX%d =", numeroCongruenze, numeroCongruenze);

            for (int i=0; i<numeroCongruenze-1; i++) printf(" %d*%d +",Rn[i], Xn[i]);
            printf(" %d*%d =", Rn[numeroCongruenze-1], Xn[numeroCongruenze-1]);

            for (int i=0; i<numeroCongruenze-1; i++) printf(" %d +", Rn[i]*Xn[i]);
            printf(" %d ", Rn[numeroCongruenze-1]*Xn[numeroCongruenze-1]);

            for (int i=0; i<numeroCongruenze; i++) X=X+(Rn[i]*Xn[i]);
            printf("= %d.\n\n  %d e' l'unica soluzione del sistema modulo %d.\n", X, X, R);

            if (X<0) while (X>=0 && X+R>=0) X+=R;
            else while (X>=0 && X-R>=0) X-=R;

            printf("\n  La piu' piccola soluzione positiva del sistema e' %d.\n  Tutte le soluzioni sono del tipo %d + %dh, con h appartenente a Z.\n",X,X,R);
        }
        printf("\n  Digitare 1 per risolvere un altro sistema: ");
        scanf("%d", &GoStop);
        printf("\n");

    } while(GoStop == 1);

    return 0;
}

int calcoloMCD(int a, int b) {

    int c;
    if (a<0) a = -a;
    if (b<0) b = -b;

    while (a!=b) {

        if (a<b) {
            c=a;
            a=b;
            b=c;
        }
        a-=b;
    }
    return b;
}

void graphic(int numeroCongruenze, int i) {

    if (numeroCongruenze % 2 == 0) {

        if (i==((numeroCongruenze/2)-1))
            printf(" _");
        else
            printf("  ");
    }
    else {
        if (i==numeroCongruenze/2)
            printf(" -");
        else
            printf("  ");
    }
}

void print(int a, int b, int mod) {

    if (a == 1)
        printf("| x");

    else if (a == -1)
        printf("| -x");

    else
        printf("| %dx", a);

    printf(" congruo a %d mod %d\n", b, mod);
}
