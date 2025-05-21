# wav2midi

## 克隆仓库

```bash
git clone --recursive https://github.com/ExMingYan/wav2midi.git
```

## 编译

### 依赖库

```plaintext
sndfile fftw3 midifile
```

注意：midifile库会在编译wav2midi时自动编译

### 生成

```bash
make
```

### 清理

如果想连带midifile库一起清除，使用以下命令

```
make clean
```

如果仅想清除wav2midi，使用以下命令

```
make tidy
```
