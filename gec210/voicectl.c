//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  File name: GPLE/voicectl.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2017-01
//  
//  Description: 获取语音指令，根据指令完成相应动作
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "common.h"

#define REC_CMD  "./arecord -d3 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define PCM_FILE "./cmd.pcm"

void catch(int sig)
{
	if(sig == SIGPIPE)
	{
		printf("killed by SIGPIPE\n");
		exit(0);
	}
}

int main(int argc, char const *argv[]) // ./wav2pcm ubuntu-IP
{
	signal(SIGPIPE, catch);

	if(argc != 2)
	{
		printf("Usage: %s <ubuntu-IP>\n", argv[0]);
		exit(0);
	}

	int sockfd = init_sock(argv[1]);
	char *FB = init_lcd();
	
	printf("waiting for result...\n");
	while(1)
	{
		// 1，调用arecord来录一段音频
		printf("press LCD to start REC in 3s...\n");
		wait4touch();
		system(REC_CMD);

		// 2，将录制好的PCM音频发送给语音识别引擎
		send_pcm(sockfd, PCM_FILE);

		// 3，等待对方回送识别结果（字符串ID）
		xmlChar *id = wait4id(sockfd);
		if(id == NULL)
			continue;

		if(atoi((char *)id) == 999)
		{
			printf("bye-bye!\n");
			break;
		}

		printf("id: %s\n", (char *)id);
		show_someone(FB, atoi((char *)id));
	}

	close(sockfd);
	return 0;
}

