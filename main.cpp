#include <iostream>
#include <vector>
#include <map>
#include <string>

#define      KART_ADEDI      52
#define      SENSITIVITY      .1

using namespace std;

typedef enum _Renk { SINEK, KARO, KUPA, MACA }Renk;
typedef enum _Deger { IKI, UC, DORT, BES, ALTI, YEDI, SEKIZ, DOKUZ, ON, VALE, KIZ, PAPAZ, AS } Deger;

vector<string> degerler{ "2","3","4","5","6","7","8","9","10","Vale","Kiz","Papaz","As" };
vector<string> renkler{ "sinek", "karo", "kupa", "maca" };

struct Kart {
	Renk renk;
	Deger deger;
}kart;

class Deste {
public:
	vector<Kart> deste;
	vector<Kart> kartlarim;
	vector<int> kartnum{ 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int ardisil[4][13] = { 0 };
	bool ardisilMi[4][13] = { false };
	int elsay�s� = 0;

	virtual void ekranabas(Kart p) {
		cout << renkler[p.renk] << "" << degerler[p.deger] << "\n";
	}

	void deste_karistir() {
		int kar_der = rand() % 500 + 100;
		int k;
		for (k = 0; k < kar_der; ++k) {
			int num = rand() % KART_ADEDI;
			Kart temp = deste[k % KART_ADEDI];
			deste[k % KART_ADEDI] = deste[num];
			deste[num] = temp;
		}
	}

	virtual void kartekle(Kart kart) {
		deste.push_back(kart);
	}

	void kartekledeste(Kart kart) {
		deste.push_back(kart);
	}

	virtual Kart kartcikar(Kart kart) {
		for (int i = 0; i < deste.size(); i++) {
			if (deste[i].deger == kart.deger && deste[i].renk == kart.renk)
				deste.erase(deste.begin() + i);
		}
		return kart;
	}

	virtual Kart kart_cek() {
		Kart kart;
		if (!deste.size()) {
			cout << "destede kagit kalmadi\n";
			cout << "Sonuc : Beraberlik";
			exit(EXIT_FAILURE);
		}
		kart = deste[deste.size() - 1];
		deste.pop_back();
		return kart;
	}

	Kart kart_cekdeste()
	{
		Kart kart;
		if (!deste.size()) {
			cout << "destede kagit kalmadi\n";
			cout << "Sonuc : Beraberlik";
			exit(EXIT_FAILURE);
		}
		kart = deste[deste.size() - 1];
		deste.pop_back();
		return kart;
	}

	Kart kart_yap(Kart p, Renk r, Deger d)
	{
		p.renk = r;
		p.deger = d;
		return p;
	}

	void deste_yap()
	{
		int i;
		for (i = 0; i < KART_ADEDI; ++i) {
			kart = kart_yap(kart, Renk(i / 13), Deger(i % 13));
			kartekledeste(kart);
		}
	}

	void kart_takas_et(Kart p1, Kart p2)
	{
		Kart temp = p1;
		p1 = p2;
		p2 = temp;
	}

	virtual bool checkPerSame(int index) {
		return kartnum[index] >= 3 ? true : false;
	}

	void deste_yaz()
	{
		int i;

		for (i = 0; i < KART_ADEDI; ++i) {
			if (i && i % 13 == 0)
				printf("\n");
			ekranabas(deste[i]);
			printf(" ");
		}
	}
};

class El : public Deste {
public:
	void ekranabas(Kart p) {
		cout << renkler[p.renk] << "" << degerler[p.deger] << "\n";
	}

	Kart kart_yap(Kart p, Renk r, Deger d)
	{
		p.renk = r;
		p.deger = d;
		return p;
	}

	Kart kart_cek()
	{
		Kart kart;
		if (!deste.size()) {
			printf("destede kagit kalmadi\n");
			printf("Beraberlik\n");
			exit(EXIT_FAILURE);
		}
		kart = kartlarim[kartlarim.size() - 1];
		kartlarim.pop_back();
		return kart;
	}

	void kartekle(Kart kart) {
		kartlarim.push_back(kart);
		kartnum[kart.deger]++;
		ardisil[kart.renk][kart.deger]++;
		int curr = kart.deger;
		int left = curr - 1, right = curr + 1;
		int tempR = right, tempL = left;
		while ((tempR < 13 && ardisil[kart.renk][tempR]) || (tempL >= 0 && ardisil[kart.renk][tempL])) {
			int count = 1;
			if (ardisil[kart.renk][tempL] && ardisil[kart.renk][tempR]) {
				ardisilMi[kart.renk][kart.deger] = true;
				while (tempL >= 0 && ardisil[kart.renk][tempL]) {
					ardisilMi[kart.renk][tempL] = true;
					tempL--;
				}
				while (tempR < 13 && ardisil[kart.renk][tempR]) {
					ardisilMi[kart.renk][tempR] = true;
					tempR++;
				}
			}
			else if (tempL >= 0 && ardisil[kart.renk][tempL]) {
				tempL--;
				count++;
				while (tempL >= 0 && ardisil[kart.renk][tempL]) {
					if (count == 2) {
						ardisilMi[kart.renk][tempL + 1] = true;
						ardisilMi[kart.renk][curr] = true;
					}
					count++;
					ardisilMi[kart.renk][tempL] = true;
					tempL--;
				}
			}
			else if (tempR <= 12 && ardisil[kart.renk][tempR]) {
				tempR++;
				count++;
				while (tempR < 13 && ardisil[kart.renk][tempR]) {
					if (count == 2) {
						ardisilMi[kart.renk][tempR - 1] = true;
						ardisilMi[kart.renk][curr] = true;
					}
					count++;
					ardisilMi[kart.renk][tempR] = true;
					tempR++;
				}
			}
		}
	}

	Kart kartcikar(Kart kart) {
		for (int k = 0; k < kartlarim.size(); k++) {
			if (kartlarim[k].renk == kart.renk && kartlarim[k].deger == kart.deger) {
				Kart ka;
				ka.deger = kart.deger;
				ka.renk = kart.renk;
				kartnum[ka.deger]--;
				kartlarim.erase(kartlarim.begin() + k, kartlarim.begin() + k + 1);
				k--;
			}
		}
		return kart;
	}

	bool checkPerSame(int index) {
		return kartnum[index] >= 3 ? true : false;
	}
};

bool oyna(El* player, Deste* destem, Kart* yer, string oyuncuName) {
	Renk r;
	Deger d;
	string renk, deger;
	char c;
	bool res = true;

	for (int i = 0; i < player->kartlarim.size(); i++) {
		if (player->checkPerSame(player->kartlarim[i].deger) ||
			player->ardisilMi[player->kartlarim[i].renk][player->kartlarim[i].deger]) continue;
		else res = false;
	}
	if (res) {
		cout << "\n" << "Tebrikler " << oyuncuName << " Kazandi ";
		return res;
	}
	cout << "\n" << oyuncuName << "\n Yerden mi Desteden mi kart cekmek istiyorsunuz (Y,D) : ";
	cin >> c;
	Kart cekilen_kart;
	if (c == 'd') cekilen_kart = destem->kart_cek();
	else {
		cekilen_kart.renk = yer->renk;
		cekilen_kart.deger = yer->deger;
	}
	res = true;
	player->kartekle(cekilen_kart);
	for (int i = 0; i < player->kartlarim.size(); i++) {
		if (player->checkPerSame(player->kartlarim[i].deger) ||
			player->ardisilMi[player->kartlarim[i].renk][player->kartlarim[i].deger]) continue;
		else res = false;
	}
	if (res) {
		cout << "\n" << "Tebrikler " << oyuncuName << " Kazandi! ";
		return res;
	}
	cout << "El sayisi : " << ++player->elsay�s� << "\n";
	for (int j = 0; j < renkler.size(); j++) {
		for (int i = 0; i < player->kartlarim.size(); i++)
			if (!player->checkPerSame(player->kartlarim[i].deger) &&
				!player->ardisilMi[player->kartlarim[i].renk][player->kartlarim[i].deger]
				&& int(player->kartlarim[i].renk) == j)
				cout << renkler[player->kartlarim[i].renk] << "" << degerler[player->kartlarim[i].deger] << "  ";
	}
	bool renkYanlis = true, degerYanlis = true;
	while (renkYanlis) {
		cout << "\nKart Rengi giriniz(sinek, kupa, karo, maca): ";
		cin >> renk;
		for (int i = 0; i < player->kartlarim.size(); i++) {
			if (renk == renkler[player->kartlarim[i].renk]) {
				renkYanlis = false;
				break;
			}
			if (i == (player->kartlarim.size() - 1))
				cout << "Gecerli bir Renk Giriniz! ";
		}
	}
	while (degerYanlis) {
		cout << "Kart Degeri giriniz : ";
		cin >> deger;
		for (int i = 0; i < player->kartlarim.size(); i++) {
			if (renkler[player->kartlarim[i].renk] == renk && deger == degerler[player->kartlarim[i].deger]) {
				degerYanlis = false;
				break;
			}
			if (i == (player->kartlarim.size() - 1))
				cout << "Gecerli bir Deger Giriniz! ";
		}
	}

	for (int i = 0; i < renkler.size(); i++) {
		if (renk == renkler[i]) r = Renk(i);
	}
	for (int i = 0; i < degerler.size(); i++) {
		if (deger == degerler[i]) d = Deger(i);
	}
	kart = player->kart_yap(kart, r, d);
	yer->deger = kart.deger;
	yer->renk = kart.renk;
	player->kartcikar(kart);
	return false;
}

int main()
{
	El player1;
	Deste* destem = &player1;
	Kart* yer = new Kart();
	destem->deste_yap();		
	destem->deste_karistir();				

	El* player = &player1;
	El* computer = new El();

	//oyunculara kart da��t
	for (int i = 0; i < 14; i++) {
		Kart cekilen_kart1 = destem->kart_cekdeste();
		computer->kartekle(cekilen_kart1);
		Kart cekilen_kart2 = destem->kart_cekdeste();
		destem->kartekle(cekilen_kart2);
	}
	bool gameOver = false;
	cout << "      .--------------------.         .--.--.                            .----------------------------------." << "\n";
	cout << "      |   Ellibir Oyununa  |       .; .;|;. ;.                          |    Kodun tekrar vermemesi icin   |" << "\n";
	cout << "      |    Hosgeldiniz!    |      .;_;'   `;_;.                         | verilen karakterleri oldugu gibi |" << "\n";
	cout << "      |     Bol Sans!!     |     ; ;'       `; ;                        |   giriniz macaVale -> maca,Vale  |" << "\n";
	cout << "      `-------------.  ,---'    ;;'.--.___.--.`;;                       |         sinek5 -> sinek,5        |" << "\n";
	cout << "                     \\|         ;-(  o )=( o  )-;                       |           Bumin, Yigit,          |" << "\n";
	cout << "                      \\        (   `--' | `--'   )                      |         Batughan ve Murat        |" << "\n";
	cout << "                                \\|     . .     |/                       |      tarafindan olusturuldu.     |" << "\n";
	cout << "                  ...........    .   .:::::.   .     .______            |   � 2021 Tum haklari saklidir.   |" << "\n";
	cout << "                 /                .   '---`   .             '\\          '----------------------------------'" << "\n";
	cout << "                .'                 `.       .'                \\ " << "\n";
	cout << "                |        ____,.- . | `.....' |   _______      | " << "\n";
	cout << "                 |    ,-'          \\        /|\\''         \\.--| " << "\n";
	cout << "                 |   /            \\.'\\     /,'.          \\. - | " << "\n";
	cout << "                 |  /|             `  `\\ /                 \\  | " << "\n";
	cout << "                |  ,/      _           '/                  '\\ |   " << "\n";
	cout << "                 ,-'     ,-.           |o                    ' " << "\n";
	cout << "                /         '|           |            | |       \\ " << "\n";
	cout << "               /         ,/|           |o           |  \\       ` " << "\n";
	cout << "              |        .'  |           |.'          |. \\        \\ " << "\n";
	cout << "     ________/       .'____|________________________||__`.       `__________" << "\n";
	cout << "            (         \\                        )        /         ) " << "\n";
	cout << "             '-.       '-.                    (      .-`       .-` " << "\n";
	cout << "                '-.    .-'--.__.             .-.__.--`-.    .-` " << "\n";
	cout << "                  '-..'     \\--'            : ~`:=,`-   `..-` " << "\n";
	cout << "                      \\ ..  \\\\              |`-'|`-,    / " << "\n";
	cout << "                       \\\\\\\\\\\\\\)             |   |`-'/.'/ " << "\n";
	cout << "                        \\)\\)\\\\               `-' `-' " << "\n";
	cout << "Oyuncu" << "\n";
	for (int j = 0; j < renkler.size(); j++) {
		for (int i = 0; i < destem->kartlarim.size(); i++) {
			if (!destem->checkPerSame(destem->kartlarim[i].deger) &&
				!destem->ardisilMi[destem->kartlarim[i].renk][destem->kartlarim[i].deger]
				&& int(destem->kartlarim[i].renk) == j) {
				cout << renkler[destem->kartlarim[i].renk] << "" << degerler[destem->kartlarim[i].deger] << "  ";
			}
		}
	}
	cout << "\nBilgisayar" << "\n";
	for (int j = 0; j < renkler.size(); j++) {
		for (int i = 0; i < computer->kartlarim.size(); i++) {
			if (!computer->checkPerSame(computer->kartlarim[i].deger) &&
				!computer->ardisilMi[computer->kartlarim[i].renk][computer->kartlarim[i].deger]
				&& int(computer->kartlarim[i].renk) == j)
				cout << renkler[computer->kartlarim[i].renk] << "" << degerler[computer->kartlarim[i].deger] << "  ";
		}
	}
	gameOver = oyna(player, destem, yer, "Oyuncu");
	cout << "\n" << endl;
	while (!gameOver) {
		gameOver = oyna(computer, destem, yer, "Bilgisayar");
		if (gameOver) break;
		gameOver = oyna(player, destem, yer, "Oyuncu");
	}
	return 0;
}
