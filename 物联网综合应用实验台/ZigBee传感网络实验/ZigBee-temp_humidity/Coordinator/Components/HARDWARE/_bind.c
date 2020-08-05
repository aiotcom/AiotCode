#include "_bind.h"
/*
�����עҪ���������ȥ�����
*/
void StartBind(uint8 NumOfId,const cId_t *pId )
{
  printf("pId=%d\r\n",*pId);
  if ( AF_DataRequest( &Boardcast_DstAddr,
                       &Coordinator_epDesc,
                       BIND_REQUEST_CMD_ID,
                       NumOfId*2,
                       (uint8*)pId,
                       &SampleApp_TransID,
                       AF_DISCV_ROUTE,
                       AF_DEFAULT_RADIUS ) == afStatus_SUCCESS )
  {
    printf("request bind\r\n");//���ڴ�ӡ��ʾ�����ͳɹ�
  }  
}
/*
�豸����������
*/
void ResponeBind(uint16 *pId,afAddrType_t *dstAddr)
{
  if ( AF_DataRequest( dstAddr,
                       &EndDevice_epDesc,
                       BIND_RSP_CMD_ID,
                       2,
                       (uint8*)pId,
                       &SampleApp_TransID,
                       AF_DISCV_ROUTE,
                       AF_DEFAULT_RADIUS ) == afStatus_SUCCESS )
  {
    printf("response bind\r\n");//���ڴ�ӡ��ʾ�����ͳɹ�
  } 
}