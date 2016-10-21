/* GStreamer
 * Copyright (C) <2005> Edgard Lima <edgard.lima@indt.org.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more 
 */


#ifndef __GST_RTP_PCMU_PAY_20_H__
#define __GST_RTP_PCMU_PAY_20_H__

#include <gst/gst.h>
#include <gst/rtp/gstrtpbaseaudiopayload.h>

G_BEGIN_DECLS

typedef struct _GstRtpPcmuPay20 GstRtpPcmuPay20;
typedef struct _GstRtpPcmuPay20Class GstRtpPcmuPay20Class;

#define GST_TYPE_RTP_PCMU_PAY20 \
  (gst_rtp_pcmu_pay20_get_type())
#define GST_RTP_PCMU_PAY20(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_RTP_PCMU_PAY20,GstRtpPcmuPay20))
#define GST_RTP_PCMU_PAY20_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_RTP_PCMU_PAY20,GstRtpPcmuPay20Class))
#define GST_IS_RTP_PCMU_PAY20(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_RTP_PCMU_PAY20))
#define GST_IS_RTP_PCMU_PAY20_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_RTP_PCMU_PAY20))

struct _GstRtpPcmuPay20
{
  GstRTPBaseAudioPayload audiopayload;
};

struct _GstRtpPcmuPay20Class
{
  GstRTPBaseAudioPayloadClass parent_class;
};

GType gst_rtp_pcmu_pay20_get_type (void);

gboolean gst_rtp_pcmu_pay20_plugin_init (GstPlugin * plugin);

G_END_DECLS

#endif /* __GST_RTP_PCMU_PAY20_H__ */