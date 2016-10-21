/*
 * (C) Copyright 2013 Kurento (http://kurento.org/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef _KMS_RECORDER_ENDPOINT_H_
#define _KMS_RECORDER_ENDPOINT_H_

#include <commons/kmsuriendpoint.h>

G_BEGIN_DECLS
#define KMS_TYPE_RECORDER_ENDPOINT \
  (kms_recorder_endpoint_get_type())
#define KMS_RECORDER_ENDPOINT(obj) (           \
  G_TYPE_CHECK_INSTANCE_CAST(                  \
    (obj),                                     \
    KMS_TYPE_RECORDER_ENDPOINT,                \
    LolKmsRecorderEndpoint                        \
  )                                            \
)
#define KMS_RECORDER_ENDPOINT_CLASS(klass) (   \
  G_TYPE_CHECK_CLASS_CAST (                    \
    (klass),                                   \
    KMS_TYPE_RECORDER_ENDPOINT,                \
    LolKmsRecorderEndpointClass                   \
  )                                            \
)
#define KMS_IS_RECORDER_ENDPOINT(obj) (        \
  G_TYPE_CHECK_INSTANCE_TYPE (                 \
    (obj),                                     \
    KMS_TYPE_RECORDER_ENDPOINT                 \
  )                                            \
)
#define KMS_IS_RECORDER_ENDPOINT_CLASS(klass) (         \
  G_TYPE_CHECK_CLASS_TYPE((klass),                      \
  KMS_TYPE_RECORDER_ENDPOINT)                           \
)
typedef struct _LolKmsRecorderEndpoint LolKmsRecorderEndpoint;
typedef struct _LolKmsRecorderEndpointClass LolKmsRecorderEndpointClass;
typedef struct _LolKmsRecorderEndpointPrivate LolKmsRecorderEndpointPrivate;

struct _LolKmsRecorderEndpoint
{
  KmsUriEndpoint parent;

  /*< private > */
  LolKmsRecorderEndpointPrivate *priv;
};

struct _LolKmsRecorderEndpointClass
{
  KmsUriEndpointClass parent_class;
};

GType kms_recorder_endpoint_get_type (void);

gboolean kms_recorder_endpoint_plugin_init (GstPlugin * plugin);

G_END_DECLS
#endif
