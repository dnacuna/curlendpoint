/* GStreamer
 * Copyright (C) <1999> Erik Walthinsen <omega@cse.ogi.edu>
 * Copyright (C) <2005> Edgard Lima <edgard.lima@indt.org.br>
 * Copyright (C) <2005> Nokia Corporation <kai.vehmanen@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <gst/rtp/gstrtpbuffer.h>

#include "gstrtppcmupay20.h"
#include "gstrtppcmapay.h"
#define DEFAULT_MIN_PTIME (20*GST_MSECOND)
static GstStaticPadTemplate gst_rtp_pcmu_pay20_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("audio/x-mulaw, channels=(int)1, rate=(int)8000")
    );

static GstStaticPadTemplate gst_rtp_pcmu_pay20_src_template =
    GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("application/x-rtp, "
        "media = (string) \"audio\", "
        "payload = (int) " GST_RTP_PAYLOAD_PCMU_STRING ", "
        "clock-rate = (int) 8000, " "encoding-name = (string) \"PCMU\"; "
        "application/x-rtp, "
        "media = (string) \"audio\", "
        "payload = (int) " GST_RTP_PAYLOAD_DYNAMIC_STRING ", "
        "clock-rate = (int) [1, MAX ], " "encoding-name = (string) \"PCMU\"")
    );

static gboolean gst_rtp_pcmu_pay20_setcaps (GstRTPBasePayload * payload,
    GstCaps * caps);

#define gst_rtp_pcmu_pay20_parent_class parent_class
G_DEFINE_TYPE (GstRtpPcmuPay20, gst_rtp_pcmu_pay20,
    GST_TYPE_RTP_BASE_AUDIO_PAYLOAD);

static void
gst_rtp_pcmu_pay20_class_init (GstRtpPcmuPay20Class * klass)
{
  GstElementClass *gstelement_class;
  GstRTPBasePayloadClass *gstrtpbasepayload_class;

  gstelement_class = (GstElementClass *) klass;
  gstrtpbasepayload_class = (GstRTPBasePayloadClass *) klass;

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_rtp_pcmu_pay20_sink_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_rtp_pcmu_pay20_src_template));

  gst_element_class_set_static_metadata (gstelement_class, "RTP PCMU payloader",
      "Codec/Payloader/Network/RTP",
      "Payload-encodes PCMU audio into a RTP packet",
      "Edgard Lima <edgard.lima@indt.org.br>");

  gstrtpbasepayload_class->set_caps = gst_rtp_pcmu_pay20_setcaps;
}

static void
gst_rtp_pcmu_pay20_init (GstRtpPcmuPay20 * rtppcmupay)
{
  GstRTPBaseAudioPayload *rtpbaseaudiopayload;

  rtpbaseaudiopayload = GST_RTP_BASE_AUDIO_PAYLOAD (rtppcmupay);

  GST_RTP_BASE_PAYLOAD (rtppcmupay)->pt = GST_RTP_PAYLOAD_PCMU;
  GST_RTP_BASE_PAYLOAD (rtppcmupay)->clock_rate = 8000;

  /* tell rtpbaseaudiopayload that this is a sample based codec */
  gst_rtp_base_audio_payload_set_sample_based (rtpbaseaudiopayload);

  /* octet-per-sample is 1 for PCM */
  gst_rtp_base_audio_payload_set_sample_options (rtpbaseaudiopayload, 1);
  g_object_set (rtppcmupay, "min-ptime", DEFAULT_MIN_PTIME, NULL);

}

static gboolean
gst_rtp_pcmu_pay20_setcaps (GstRTPBasePayload * payload, GstCaps * caps)
{
  gboolean res;

  gst_rtp_base_payload_set_options (payload, "audio",
      payload->pt != GST_RTP_PAYLOAD_PCMU, "PCMU", 8000);
  res = gst_rtp_base_payload_set_outcaps (payload, NULL);

  return res;
}

gboolean
gst_rtp_pcmu_pay20_plugin_init (GstPlugin * plugin)
{
  return gst_element_register (plugin, "rtppcmupay20",
      GST_RANK_PRIMARY+1, GST_TYPE_RTP_PCMU_PAY20);
}
static gboolean
plugin_init (GstPlugin * plugin)
{
  if (!gst_rtp_pcma_pay_plugin_init(plugin)) {
    return FALSE;
  }
  return gst_rtp_pcmu_pay20_plugin_init(plugin);
}
GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    rtppcmupay20,
    "PCMU payloader with min ptime set to 20 ms",
    plugin_init, VERSION, GST_LICENSE_UNKNOWN, "PACKAGE_NAME", "origin")
