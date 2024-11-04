#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fungsi persamaan f(x) = x^3 - 2x^2 - 5
double f(double x) {
    return (x * x * x) - 2 * (x * x) - 5;
    // return (x*x*x) + (x*x) - (3*x) - 3;
}

// regula falsi c = b - fb * (b - a) / (fb - fa);

// Fungsi metode tabel
void table(double a, double b, double step) {
    double x1, y1, y2;
    int batasError = 0;  // Menandakan apakah akar ditemukan

    for (x1 = a; x1 <= b; x1 += step) {
        y1 = f(x1);
        y2 = f(x1 + step);

        printf("f(%.2f) = %.2f\n", x1, y1);

        if (y1 * y2 < 0) {
            printf("Akar ditemukan di antara %.2f dan %.2f\n", x1, x1 + step);
            batasError = 1;
        } else if (fabs(y1) < 1e-6) {
            printf("Akar ditemukan tepat di x = %.2f\n", x1);
            batasError = 1;
        }
    }

    if (!batasError) {
        printf("Tidak ada akar yang ditemukan dalam interval yang diberikan.\n");
    }
}

// Fungsi metode bisection
void bisection(double a, double b, double batasError) {
    double c; // akar
    int i = 1;

    // check apakah ada akar diantara titik a dan b
    if (f(a) * f(b) >= 0) {
        printf("Tidak ada akar antara %.2f dan %.2f\n", a, b);
        return;
    }

    // fc = error
    printf("a\tb\tc\tf(c)\n");
    printf("-------------------------------\n");

    // if fc > batas error go looping
   do {
    c = (a+b) / 2;

    printf("%.5f\t%.5f\t%.5f\t%.5f\n", a, b, c, fabs(f(c)));

    // logic bisection
    if (fabs(f(c)) < batasError) {
        break;
    } else if (f(a) * f(c) < 0) {
        // tandanya berbeda
        b = c;
    } else {
        // tandanya sama
        a = c;
    }

    i++;

} while (fabs(f(c)) > batasError);

    printf("Akar yang ditemukan: %.5f setelah %d iterasi\n", c, i);
    printf("Toleransi error: %.5f\n", fabs(f(c)));
}


// Fungsi metode regula falsi
void regula_falsi(double a, double b, double batasError) {
    double c;
    int i = 1; 

    // check apakah ada akar diantara titik a dan b
    if (f(a) * f(b) >= 0) {
        printf("Tidak ada akar antara %.2f dan %.2f\n", a, b);
        return;
    }

     printf("a\tb\tc\terror\n");
    printf("-------------------------------\n");

 // if fc > batas error go looping

do {
    c = a - f(a) * (b - a) / (f(b) - f(a));
    
    printf("%.5f\t%.5f\t%.5f\t%.5f\n", a, b, c, fabs(f(c)));

    if (fabs(f(c)) < batasError) {
        break;
    } else if (f(a) * f(c) < 0) {
        b = c;
    } else {
        a = c;
    }

    i++;
} while (fabs(f(c)) > batasError);


    printf("Akar yang ditemukan: %.5f setelah %d iterasi\n", c, i);
    printf("Toleransi error: %.5f\n", fabs(f(c)));
}

// Newton Naphson

// create turunan function
double turunan(double x) {
    // 3x^2 - 4x
    return 3 * x * x - 4 * x;
    // return (3 * (x*x)) + (2*x) - 3;
}

void newtonRaphson(double x0, double batasError) {
    // mencari akar persamaan non linear dengan metode terbuka
    // x0 = xi = tebakan awal
    // x1 = xi + 1

    double x1;
    int iteration = 1; // iterasi dimulai dari angka 1

    // Iterasi hingga error lebih kecil dari batas error maka looping berhenti
    do {
        // check turunan agar tidak bernilai 0 atau tidak terdefinisi
        if (turunan(x0) == 0) {
            printf("Pembagian tidak boleh dilakukan oleh 0\n");
            return;
        }

        // rumus newton raphson
        x1 = x0 - f(x0) / turunan(x0); 

        // Mencetak hasil setiap iterasi
        printf("Iterasi %d: x0 = %.5f, x1 = %.5f, f(x1) = %.5f\n", iteration, x0, x1, f(x1));

        // Menyiapkan x0 untuk iterasi berikutnya
        x0 = x1;
        iteration++;

    } while (fabs(f(x1)) > batasError);

    printf("Akar ditemukan: %.5f setelah %d iterasi dengan error %.5f\n", x1, iteration, f(x1));
}


// Menu utama program dengan switch-case
int main() {
    int choice;
    double a, b, x0, batasError, step;

    do {
        // Menu pilihan metode
        printf("\nPilih metode pencarian akar:\n");
        printf("1. Metode Tabel\n");
        printf("2. Metode Bisection\n");
        printf("3. Metode Regula Falsi\n");
        printf("4. Metode Newton Raphson\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Input untuk metode tabel
                printf("Masukkan batas bawah: ");
                scanf("%lf", &a);
                printf("Masukkan batas atas: ");
                scanf("%lf", &b);
                printf("Masukkan step: ");
                scanf("%lf", &step);
                table(a, b, step);
                break;

            case 2:
                // Input untuk metode bisection
                printf("Masukkan batas bawah: ");
                scanf("%lf", &a);
                printf("Masukkan batas atas: ");
                scanf("%lf", &b);
                printf("Masukkan toleransi error: ");
                scanf("%lf", &batasError);
                bisection(a, b, batasError);
                break;

            case 3:
                // Input untuk metode regula falsi
                printf("Masukkan batas bawah: ");
                scanf("%lf", &a);
                printf("Masukkan batas atas: ");
                scanf("%lf", &b);
                printf("Masukkan toleransi error: ");
                scanf("%lf", &batasError);
                regula_falsi(a, b, batasError);
                break;


            case 4: 
                // Input untuk metode Newton-Raphson
                printf("Masukkan nilai awal: ");
                scanf("%lf", &x0);
                printf("Masukkan toleransi error: ");
                scanf("%lf", &batasError);
                newtonRaphson(x0, batasError);
                break;


            case 5:
                printf("Program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice !=5);

    return 0;
}
