# Chess Master

이 프로젝트는 **C++** 와 **`SFML`** 라이브러리를 사용하여 만든 2D 체스 게임입니다. 게임의 상대방은 **Stockfish** 체스 엔진을 통해 제어됩니다.

## 🕹️ **게임 규칙**
- 이 게임은 **체스**의 전통적인 규칙에 따라 진행됩니다.
- **앙파상 (En Passant)**, **프로모션 (Promotion)**, **캐슬링 (Castling)** 이 가능합니다.
- **게임 종료**: `Esc` 키를 누르면 게임이 종료됩니다.
- **게임 재시작**: `R` 키를 누르면 게임이 재시작됩니다.

## 🤖 **AI 상대 (Stockfish)**  
이 게임의 상대는 **Stockfish** 체스 엔진을 사용하여 구현된 AI입니다. **Stockfish**는 고성능 체스 엔진으로, 플레이어의 움직임을 바탕으로 최적의 수를 계산하여 기물을 이동시킵니다. 사용자는 AI와의 대전을 통해 게임을 진행할 수 있습니다.

## 💻 **실행 방법**

### 1. **SFML 설치**
이 프로젝트는 **SFML (Simple and Fast Multimedia Library)**을 사용하여 그래픽 및 오디오 처리를 합니다. SFML이 설치되지 않으면 게임을 빌드하거나 실행할 수 없습니다. 아래 방법으로 SFML을 설치합니다.

- **Ubuntu / Debian**
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

- **Windows**

Windows에서 SFML을 설치하려면, 아래 절차를 따라주세요.

1. [SFML 다운로드 페이지](https://www.sfml-dev.org/download.php)에서 Windows용 SFML을 다운로드합니다.
2. 다운로드한 ZIP 파일을 압축 해제하고, **SFML**의 **라이브러리**와 **헤더** 파일을 C++ IDE(예: Visual Studio)에 맞게 설정합니다.

#### 설정 방법:

- Visual Studio나 다른 C++ IDE에서 프로젝트의 속성에서 SFML 라이브러리와 헤더 파일 경로를 설정합니다.
- SFML을 프로젝트에 링크하려면 `sfml-graphics`, `sfml-window`, `sfml-system` 등의 라이브러리를 추가해야 합니다.

### 2. Stockfish 설치

이 프로젝트는 Stockfish 체스 엔진을 사용하여 AI와의 대전을 가능하게 합니다. Stockfish를 설치하려면 아래 절차를 따라주세요.

#### Stockfish 다운로드

- Stockfish GitHub 페이지에서 최신 버전의 Stockfish를 다운로드합니다.  
- GitHub에서 직접 다운로드하거나, 아래 명령어로 클론할 수 있습니다:

```bash
git clone https://github.com/official-stockfish/Stockfish.git
cd Stockfish
```

#### Stockfish 빌드

- Ubuntu / Debian에서 Stockfish를 빌드하려면, 먼저 필요한 패키지를 설치해야 합니다:

```bash
sudo apt-get install build-essential
sudo apt-get install clang
sudo apt-get install libboost-system-dev
```

- 이후, Stockfish를 빌드합니다:

```bash
make
```

- 빌드가 완료되면, stockfish 실행 파일이 생성됩니다.

#### Windows에서 Stockfish 사용

1. [Stockfish 다운로드 페이지](https://github.com/official-stockfish/Stockfish)에서 Windows용 실행 파일을 다운로드합니다.
2. 다운로드한 `.zip` 파일을 압축 해제합니다.
3. Stockfish 실행 파일을 `chess-master` 프로젝트 디렉토리에 직접 배치합니다.

### 3. 프로젝트 클론

Git을 사용하여 프로젝트를 클론합니다:

```bash
git clone https://github.com/seonjae01/chess-master.git
cd chess-master
```

### 4. 빌드

Makefile을 사용하여 빌드를 진행하려면, 프로젝트 루트 디렉토리에서 아래 명령어를 실행합니다:

```bash
make
```

### 5. 게임 실행

빌드가 완료되면 아래 명령어로 게임을 실행할 수 있습니다:

```bash
./chessmaster
```

## 📋 프로젝트 구조

```bash
.
├── Makefile               # Makefile 빌드 설정 파일
├── LICENSE                # 프로젝트 라이선스 파일
├── README.md              # 프로젝트 설명 파일
├── sounds/                # 게임에 사용할 오디오 디렉토리
├── images/                # 게임에 사용할 이미지 디렉토리
├── fonts/                 # 게임에 사용할 폰트 디렉토리
├── src/                   # 소스 코드 디렉토리
    ├── main.cpp           # 게임의 메인 소스 파일
    ├── board.cpp          # 체스 보드 관련 로직
    ├── board.hpp
    ├── engine.cpp         # AI 관련 로직
    ├── engine.hpp
    ├── game.cpp           # 기본 게임 로직
    ├── game.hpp
    ├── piece.cpp          # 기물 관련 로직
    ├── piece.hpp
    ├── sounds.cpp         # 게임 소리 관련 로직
    └── sounds.hpp
```

## 🛠️ 빌드 에러 해결

1. **`SFML` 라이브러리 설치:**

    - 이 프로젝트는 **SFML (Simple and Fast Multimedia Library)** 을 사용하여 그래픽 및 오디오 처리를 합니다. SFML이 설치되지 않으면 게임을 빌드하거나 실행할 수 없습니다.

2. **C++ 버전 확인:**

    - 이 프로젝트는 C++17 이상의 버전을 필요로 합니다. 사용 중인 C++ 컴파일러가 C++17 이상을 지원하는지 확인해야 합니다. 만약 C++17을 지원하지 않는 컴파일러를 사용하고 있다면, 컴파일러를 업데이트하거나 C++17을 지원하는 버전을 사용해야 합니다.

    - 아래 명령어로 현재 사용 중인 C++ 컴파일러가 C++17을 지원하는지 확인합니다:

```bash
g++ --version
```
