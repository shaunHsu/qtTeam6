# shazam part

需先轉換格式後再行請求

```c++
    #include "AudioProcessor.h"
    #include "shazamrequest.h"

    AudioProcessor processor;
    processor.processAudioFile(fileName);//轉換為base64

    while (!processor.isProcessingFinished) {
        QCoreApplication::processEvents();
    }//等待轉換完成

    ShazamRequest request;
    request.sendRequest(&fileName, processor.audioData);//將base64傳送至shazam
```
