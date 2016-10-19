/**
 * @brief An aushape raw audit log converter output buffer
 *
 * Copyright (C) 2016 Red Hat
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _AUSHAPE_CONV_BUF_H
#define _AUSHAPE_CONV_BUF_H

#include <aushape/conv/execve.h>
#include <aushape/conv/rc.h>
#include <auparse.h>

/** Converter's output buffer */
struct aushape_conv_buf {
    /** Growing buffer for an output piece */
    struct aushape_gbuf         gbuf;
    /** Execve record aggregation state */
    struct aushape_conv_execve  execve;
};

/**
 * Check if a converter output buffer is valid.
 *
 * @param buf   The buffer to check.
 *
 * @return True if the buffer is valid, false otherwise.
 */
extern bool aushape_conv_buf_is_valid(const struct aushape_conv_buf *buf);

/**
 * Initialize a converter output buffer
 *
 * @param buf   The buffer to initialize.
 */
extern void aushape_conv_buf_init(struct aushape_conv_buf *buf);

/**
 * Cleanup a converter output buffer (free allocated data).
 *
 * @param buf   The buffer to cleanup.
 */
extern void aushape_conv_buf_cleanup(struct aushape_conv_buf *buf);

/**
 * Empty a converter output buffer - prepare for processing of another event.
 *
 * @param buf   The buffer to empty.
 */
extern void aushape_conv_buf_empty(struct aushape_conv_buf *buf);

/**
 * Add a formatted fragment for an auparse event to a converter output buffer.
 *
 * @param buf       The converter buffer to add the fragment to.
 * @param format    The output format to use.
 * @param level     Syntactic nesting level the event is output at.
 * @param au        The auparse state with the current event as the one to be
 *                  output.
 *
 * @return Return code:
 *          AUSHAPE_CONV_RC_OK              - added succesfully,
 *          AUSHAPE_CONV_RC_NOMEM           - memory allocation failed,
 *          AUSHAPE_CONV_RC_AUPARSE_FAILED  - an auparse call failed,
 *          AUSHAPE_CONV_RC_INVALID_EXECVE  - invalid execve record sequence
 *                                            encountered.
 */
extern enum aushape_conv_rc aushape_conv_buf_add_event(
                                    struct aushape_conv_buf *buf,
                                    const struct aushape_format *format,
                                    size_t level,
                                    auparse_state_t *au);

#endif /* _AUSHAPE_CONV_BUF_H */
