/**
 * \file
 * Protosocket library header file
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __PSOCK_H__
#define __PSOCK_H__

#include "uipopt.h"
#include "pt.h"

 /*
 * The structure that holds the state of a buffer.
 *
 * This structure holds the state of a uIP buffer. The structure has
 * no user-visible elements, but is used through the functions
 * provided by the library.
 *
 */
struct psock_buf {
  u8_t *ptr;
  unsigned short left;
};

/**
 * The representation of a protosocket.
 *
 * The protosocket structrure is an opaque structure with no user-visible
 * elements.
 */
struct psock {
  struct pt pt, psockpt; /* Protothreads - one that's using the psock
			    functions, and one that runs inside the
			    psock functions. */
  const u8_t *sendptr;   /* Pointer to the next data to be sent. */
  u8_t *readptr;         /* Pointer to the next data to be read. */
  
  char *bufptr;          /* Pointer to the buffer used for buffering
			    incoming data. */
  
  u16_t sendlen;         /* The number of bytes left to be sent. */
  u16_t readlen;         /* The number of bytes left to be read. */

  struct psock_buf buf;  /* The structure holding the state of the
			    input buffer. */
  unsigned int bufsize;  /* The size of the input buffer. */
  
  unsigned char state;   /* The state of the protosocket. */
};

void psock_init(struct psock *psock, char *buffer, unsigned int buffersize);
/**
 * Initialize a protosocket.
 *
 * This macro initializes a protosocket and must be called before the
 * protosocket is used. The initialization also specifies the input buffer
 * for the protosocket.
 *
 * \param psock (struct psock *) A pointer to the protosocket to be
 * initialized
 *
 * \param buffer (char *) A pointer to the input buffer for the
 * protosocket.
 *
 * \param buffersize (unsigned int) The size of the input buffer.
 *
 * \hideinitializer
 */
#define PSOCK_INIT(psock, buffer, buffersize) \
  psock_init(psock, buffer, buffersize)

/**
 * Start the protosocket protothread in a function.
 *
 * This macro starts the protothread associated with the protosocket and
 * must come before other protosocket calls in the function it is used.
 *
 * \param psock (struct psock *) A pointer to the protosocket to be
 * started.
 *
 * \hideinitializer
 */
#define PSOCK_BEGIN(psock) PT_BEGIN(&((psock)->pt))

PT_THREAD(psock_send(struct psock *psock, const char *buf, unsigned int len));
/**
 * Send data.
 *
 * This macro sends data over a protosocket. The protosocket protothread blocks
 * until all data has been sent and is known to have been received by
 * the remote end of the TCP connection.
 *
 * \param psock (struct psock *) A pointer to the protosocket over which
 * data is to be sent.
 *
 * \param data (char *) A pointer to the data that is to be sent.
 *
 * \param datalen (unsigned int) The length of the data that is to be
 * sent.
 *
 * \hideinitializer
 */
#define PSOCK_SEND(psock, data, datalen)		\
    PT_WAIT_THREAD(&((psock)->pt), psock_send(psock, data, datalen))

/**
 * \brief      Send a null-terminated string.
 * \param psock Pointer to the protosocket.
 * \param str  The string to be sent.
 *
 *             This function sends a null-terminated string over the
 *             protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_SEND_STR(psock, str)      		\
    PT_WAIT_THREAD(&((psock)->pt), psock_send(psock, str, strlen(str)))

PT_THREAD(psock_generator_send(struct psock *psock,
				unsigned short (*f)(void *), void *arg));

/**
 * \brief      Generate data with a function and send it
 * \param psock Pointer to the protosocket.
 * \param generator Pointer to the generator function
 * \param arg   Argument to the generator function
 *
 *             This function generates data and sends it over the
 *             protosocket. This can be used to dynamically generate
 *             data for a transmission, instead of generating the data
 *             in a buffer beforehand. This function reduces the need for
 *             buffer memory. The generator function is implemented by
 *             the application, and a pointer to the function is given
 *             as an argument with the call to PSOCK_GENERATOR_SEND().
 *
 *             The generator function should place the generated data
 *             directly in the uip_appdata buffer, and return the
 *             length of the generated data. The generator function is
 *             called by the protosocket layer when the data first is
 *             sent, and once for every retransmission that is needed.
 *
 * \hideinitializer
 */
#define PSOCK_GENERATOR_SEND(psock, generator, arg)     \
    PT_WAIT_THREAD(&((psock)->pt),					\
		   psock_generator_send(psock, generator, arg))


/**
 * Close a protosocket.
 *
 * This macro closes a protosocket and can only be called from within the
 * protothread in which the protosocket lives.
 *
 * \param psock (struct psock *) A pointer to the protosocket that is to
 * be closed.
 *
 * \hideinitializer
 */
#define PSOCK_CLOSE(psock) uip_close()

PT_THREAD(psock_readbuf(struct psock *psock));
/**
 * Read data until the buffer is full.
 *
 * This macro will block waiting for data and read the data into the
 * input buffer specified with the call to PSOCK_INIT(). Data is read
 * until the buffer is full..
 *
 * \param psock (struct psock *) A pointer to the protosocket from which
 * data should be read.
 *
 * \hideinitializer
 */
#define PSOCK_READBUF(psock)				\
  PT_WAIT_THREAD(&((psock)->pt), psock_readbuf(psock))

PT_THREAD(psock_readto(struct psock *psock, unsigned char c));
/**
 * Read data up to a specified character.
 *
 * This macro will block waiting for data and read the data into the
 * input buffer specified with the call to PSOCK_INIT(). Data is only
 * read until the specifieed character appears in the data stream.
 *
 * \param psock (struct psock *) A pointer to the protosocket from which
 * data should be read.
 *
 * \param c (char) The character at which to stop reading.
 *
 * \hideinitializer
 */
#define PSOCK_READTO(psock, c)				\
  PT_WAIT_THREAD(&((psock)->pt), psock_readto(psock, c))

/**
 * The length of the data that was previously read.
 *
 * This macro returns the length of the data that was previously read
 * using PSOCK_READTO() or PSOCK_READ().
 *
 * \param psock (struct psock *) A pointer to the protosocket holding the data.
 *
 * \hideinitializer
 */
#define PSOCK_DATALEN(psock) psock_datalen(psock)

u16_t psock_datalen(struct psock *psock);

/**
 * Exit the protosocket's protothread.
 *
 * This macro terminates the protothread of the protosocket and should
 * almost always be used in conjunction with PSOCK_CLOSE().
 *
 * \sa PSOCK_CLOSE_EXIT()
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_EXIT(psock) PT_EXIT(&((psock)->pt))

/**
 * Close a protosocket and exit the protosocket's protothread.
 *
 * This macro closes a protosocket and exits the protosocket's protothread.
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_CLOSE_EXIT(psock)		\
  do {						\
    PSOCK_CLOSE(psock);			\
    PSOCK_EXIT(psock);			\
  } while(0)

/**
 * Declare the end of a protosocket's protothread.
 *
 * This macro is used for declaring that the protosocket's protothread
 * ends. It must always be used together with a matching PSOCK_BEGIN()
 * macro.
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_END(psock) PT_END(&((psock)->pt))

char psock_newdata(struct psock *s);

/**
 * Check if new data has arrived on a protosocket.
 *
 * This macro is used in conjunction with the PSOCK_WAIT_UNTIL()
 * macro to check if data has arrived on a protosocket.
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_NEWDATA(psock) psock_newdata(psock)

/**
 * Wait until a condition is true.
 *
 * This macro blocks the protothread until the specified condition is
 * true. The macro PSOCK_NEWDATA() can be used to check if new data
 * arrives when the protosocket is waiting.
 *
 * Typically, this macro is used as follows:
 *
 \code
 PT_THREAD(thread(struct psock *s, struct timer *t))
 {
   PSOCK_BEGIN(s);

   PSOCK_WAIT_UNTIL(s, PSOCK_NEWADATA(s) || timer_expired(t));
   
   if(PSOCK_NEWDATA(s)) {
     PSOCK_READTO(s, '\n');
   } else {
     handle_timed_out(s);
   }
   
   PSOCK_END(s);
 }
 \endcode
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 * \param condition The condition to wait for.
 *
 * \hideinitializer
 */
#define PSOCK_WAIT_UNTIL(psock, condition)    \
  PT_WAIT_UNTIL(&((psock)->pt), (condition));

#define PSOCK_WAIT_THREAD(psock, condition)   \
  PT_WAIT_THREAD(&((psock)->pt), (condition))

#endif /* __PSOCK_H__ */

/** @} */
