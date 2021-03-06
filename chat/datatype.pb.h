// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: datatype.proto

#ifndef PROTOBUF_datatype_2eproto__INCLUDED
#define PROTOBUF_datatype_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace plumgrid {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_datatype_2eproto();
void protobuf_AssignDesc_datatype_2eproto();
void protobuf_ShutdownFile_datatype_2eproto();

class channel_info;
class control_msg;
class channel_list;
class ack;
class chat;

enum control_msg_Type {
  control_msg_Type_GET_CHANNELS = 0,
  control_msg_Type_JOIN_NOTIFICATION = 1,
  control_msg_Type_LEAVE_NOTIFICATION = 2
};
bool control_msg_Type_IsValid(int value);
const control_msg_Type control_msg_Type_Type_MIN = control_msg_Type_GET_CHANNELS;
const control_msg_Type control_msg_Type_Type_MAX = control_msg_Type_LEAVE_NOTIFICATION;
const int control_msg_Type_Type_ARRAYSIZE = control_msg_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* control_msg_Type_descriptor();
inline const ::std::string& control_msg_Type_Name(control_msg_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    control_msg_Type_descriptor(), value);
}
inline bool control_msg_Type_Parse(
    const ::std::string& name, control_msg_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<control_msg_Type>(
    control_msg_Type_descriptor(), name, value);
}
// ===================================================================

class channel_info : public ::google::protobuf::Message {
 public:
  channel_info();
  virtual ~channel_info();

  channel_info(const channel_info& from);

  inline channel_info& operator=(const channel_info& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const channel_info& default_instance();

  void Swap(channel_info* other);

  // implements Message ----------------------------------------------

  channel_info* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const channel_info& from);
  void MergeFrom(const channel_info& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string data_url = 1;
  inline bool has_data_url() const;
  inline void clear_data_url();
  static const int kDataUrlFieldNumber = 1;
  inline const ::std::string& data_url() const;
  inline void set_data_url(const ::std::string& value);
  inline void set_data_url(const char* value);
  inline void set_data_url(const char* value, size_t size);
  inline ::std::string* mutable_data_url();
  inline ::std::string* release_data_url();
  inline void set_allocated_data_url(::std::string* data_url);

  // required string control_url = 2;
  inline bool has_control_url() const;
  inline void clear_control_url();
  static const int kControlUrlFieldNumber = 2;
  inline const ::std::string& control_url() const;
  inline void set_control_url(const ::std::string& value);
  inline void set_control_url(const char* value);
  inline void set_control_url(const char* value, size_t size);
  inline ::std::string* mutable_control_url();
  inline ::std::string* release_control_url();
  inline void set_allocated_control_url(::std::string* control_url);

  // @@protoc_insertion_point(class_scope:plumgrid.channel_info)
 private:
  inline void set_has_data_url();
  inline void clear_has_data_url();
  inline void set_has_control_url();
  inline void clear_has_control_url();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* data_url_;
  ::std::string* control_url_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_datatype_2eproto();
  friend void protobuf_AssignDesc_datatype_2eproto();
  friend void protobuf_ShutdownFile_datatype_2eproto();

  void InitAsDefaultInstance();
  static channel_info* default_instance_;
};
// -------------------------------------------------------------------

class control_msg : public ::google::protobuf::Message {
 public:
  control_msg();
  virtual ~control_msg();

  control_msg(const control_msg& from);

  inline control_msg& operator=(const control_msg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const control_msg& default_instance();

  void Swap(control_msg* other);

  // implements Message ----------------------------------------------

  control_msg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const control_msg& from);
  void MergeFrom(const control_msg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef control_msg_Type Type;
  static const Type GET_CHANNELS = control_msg_Type_GET_CHANNELS;
  static const Type JOIN_NOTIFICATION = control_msg_Type_JOIN_NOTIFICATION;
  static const Type LEAVE_NOTIFICATION = control_msg_Type_LEAVE_NOTIFICATION;
  static inline bool Type_IsValid(int value) {
    return control_msg_Type_IsValid(value);
  }
  static const Type Type_MIN =
    control_msg_Type_Type_MIN;
  static const Type Type_MAX =
    control_msg_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    control_msg_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return control_msg_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return control_msg_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return control_msg_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .plumgrid.control_msg.Type type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::plumgrid::control_msg_Type type() const;
  inline void set_type(::plumgrid::control_msg_Type value);

  // optional .plumgrid.channel_info channel = 2;
  inline bool has_channel() const;
  inline void clear_channel();
  static const int kChannelFieldNumber = 2;
  inline const ::plumgrid::channel_info& channel() const;
  inline ::plumgrid::channel_info* mutable_channel();
  inline ::plumgrid::channel_info* release_channel();
  inline void set_allocated_channel(::plumgrid::channel_info* channel);

  // @@protoc_insertion_point(class_scope:plumgrid.control_msg)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_channel();
  inline void clear_has_channel();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::plumgrid::channel_info* channel_;
  int type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_datatype_2eproto();
  friend void protobuf_AssignDesc_datatype_2eproto();
  friend void protobuf_ShutdownFile_datatype_2eproto();

  void InitAsDefaultInstance();
  static control_msg* default_instance_;
};
// -------------------------------------------------------------------

class channel_list : public ::google::protobuf::Message {
 public:
  channel_list();
  virtual ~channel_list();

  channel_list(const channel_list& from);

  inline channel_list& operator=(const channel_list& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const channel_list& default_instance();

  void Swap(channel_list* other);

  // implements Message ----------------------------------------------

  channel_list* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const channel_list& from);
  void MergeFrom(const channel_list& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .plumgrid.channel_info channel = 1;
  inline int channel_size() const;
  inline void clear_channel();
  static const int kChannelFieldNumber = 1;
  inline const ::plumgrid::channel_info& channel(int index) const;
  inline ::plumgrid::channel_info* mutable_channel(int index);
  inline ::plumgrid::channel_info* add_channel();
  inline const ::google::protobuf::RepeatedPtrField< ::plumgrid::channel_info >&
      channel() const;
  inline ::google::protobuf::RepeatedPtrField< ::plumgrid::channel_info >*
      mutable_channel();

  // @@protoc_insertion_point(class_scope:plumgrid.channel_list)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::plumgrid::channel_info > channel_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_datatype_2eproto();
  friend void protobuf_AssignDesc_datatype_2eproto();
  friend void protobuf_ShutdownFile_datatype_2eproto();

  void InitAsDefaultInstance();
  static channel_list* default_instance_;
};
// -------------------------------------------------------------------

class ack : public ::google::protobuf::Message {
 public:
  ack();
  virtual ~ack();

  ack(const ack& from);

  inline ack& operator=(const ack& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ack& default_instance();

  void Swap(ack* other);

  // implements Message ----------------------------------------------

  ack* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ack& from);
  void MergeFrom(const ack& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 placeholder = 1;
  inline bool has_placeholder() const;
  inline void clear_placeholder();
  static const int kPlaceholderFieldNumber = 1;
  inline ::google::protobuf::int32 placeholder() const;
  inline void set_placeholder(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:plumgrid.ack)
 private:
  inline void set_has_placeholder();
  inline void clear_has_placeholder();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 placeholder_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_datatype_2eproto();
  friend void protobuf_AssignDesc_datatype_2eproto();
  friend void protobuf_ShutdownFile_datatype_2eproto();

  void InitAsDefaultInstance();
  static ack* default_instance_;
};
// -------------------------------------------------------------------

class chat : public ::google::protobuf::Message {
 public:
  chat();
  virtual ~chat();

  chat(const chat& from);

  inline chat& operator=(const chat& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const chat& default_instance();

  void Swap(chat* other);

  // implements Message ----------------------------------------------

  chat* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const chat& from);
  void MergeFrom(const chat& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string contents = 1;
  inline bool has_contents() const;
  inline void clear_contents();
  static const int kContentsFieldNumber = 1;
  inline const ::std::string& contents() const;
  inline void set_contents(const ::std::string& value);
  inline void set_contents(const char* value);
  inline void set_contents(const char* value, size_t size);
  inline ::std::string* mutable_contents();
  inline ::std::string* release_contents();
  inline void set_allocated_contents(::std::string* contents);

  // @@protoc_insertion_point(class_scope:plumgrid.chat)
 private:
  inline void set_has_contents();
  inline void clear_has_contents();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* contents_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_datatype_2eproto();
  friend void protobuf_AssignDesc_datatype_2eproto();
  friend void protobuf_ShutdownFile_datatype_2eproto();

  void InitAsDefaultInstance();
  static chat* default_instance_;
};
// ===================================================================


// ===================================================================

// channel_info

// required string data_url = 1;
inline bool channel_info::has_data_url() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void channel_info::set_has_data_url() {
  _has_bits_[0] |= 0x00000001u;
}
inline void channel_info::clear_has_data_url() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void channel_info::clear_data_url() {
  if (data_url_ != &::google::protobuf::internal::kEmptyString) {
    data_url_->clear();
  }
  clear_has_data_url();
}
inline const ::std::string& channel_info::data_url() const {
  return *data_url_;
}
inline void channel_info::set_data_url(const ::std::string& value) {
  set_has_data_url();
  if (data_url_ == &::google::protobuf::internal::kEmptyString) {
    data_url_ = new ::std::string;
  }
  data_url_->assign(value);
}
inline void channel_info::set_data_url(const char* value) {
  set_has_data_url();
  if (data_url_ == &::google::protobuf::internal::kEmptyString) {
    data_url_ = new ::std::string;
  }
  data_url_->assign(value);
}
inline void channel_info::set_data_url(const char* value, size_t size) {
  set_has_data_url();
  if (data_url_ == &::google::protobuf::internal::kEmptyString) {
    data_url_ = new ::std::string;
  }
  data_url_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* channel_info::mutable_data_url() {
  set_has_data_url();
  if (data_url_ == &::google::protobuf::internal::kEmptyString) {
    data_url_ = new ::std::string;
  }
  return data_url_;
}
inline ::std::string* channel_info::release_data_url() {
  clear_has_data_url();
  if (data_url_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = data_url_;
    data_url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void channel_info::set_allocated_data_url(::std::string* data_url) {
  if (data_url_ != &::google::protobuf::internal::kEmptyString) {
    delete data_url_;
  }
  if (data_url) {
    set_has_data_url();
    data_url_ = data_url;
  } else {
    clear_has_data_url();
    data_url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string control_url = 2;
inline bool channel_info::has_control_url() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void channel_info::set_has_control_url() {
  _has_bits_[0] |= 0x00000002u;
}
inline void channel_info::clear_has_control_url() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void channel_info::clear_control_url() {
  if (control_url_ != &::google::protobuf::internal::kEmptyString) {
    control_url_->clear();
  }
  clear_has_control_url();
}
inline const ::std::string& channel_info::control_url() const {
  return *control_url_;
}
inline void channel_info::set_control_url(const ::std::string& value) {
  set_has_control_url();
  if (control_url_ == &::google::protobuf::internal::kEmptyString) {
    control_url_ = new ::std::string;
  }
  control_url_->assign(value);
}
inline void channel_info::set_control_url(const char* value) {
  set_has_control_url();
  if (control_url_ == &::google::protobuf::internal::kEmptyString) {
    control_url_ = new ::std::string;
  }
  control_url_->assign(value);
}
inline void channel_info::set_control_url(const char* value, size_t size) {
  set_has_control_url();
  if (control_url_ == &::google::protobuf::internal::kEmptyString) {
    control_url_ = new ::std::string;
  }
  control_url_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* channel_info::mutable_control_url() {
  set_has_control_url();
  if (control_url_ == &::google::protobuf::internal::kEmptyString) {
    control_url_ = new ::std::string;
  }
  return control_url_;
}
inline ::std::string* channel_info::release_control_url() {
  clear_has_control_url();
  if (control_url_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = control_url_;
    control_url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void channel_info::set_allocated_control_url(::std::string* control_url) {
  if (control_url_ != &::google::protobuf::internal::kEmptyString) {
    delete control_url_;
  }
  if (control_url) {
    set_has_control_url();
    control_url_ = control_url;
  } else {
    clear_has_control_url();
    control_url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// control_msg

// required .plumgrid.control_msg.Type type = 1;
inline bool control_msg::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void control_msg::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void control_msg::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void control_msg::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::plumgrid::control_msg_Type control_msg::type() const {
  return static_cast< ::plumgrid::control_msg_Type >(type_);
}
inline void control_msg::set_type(::plumgrid::control_msg_Type value) {
  assert(::plumgrid::control_msg_Type_IsValid(value));
  set_has_type();
  type_ = value;
}

// optional .plumgrid.channel_info channel = 2;
inline bool control_msg::has_channel() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void control_msg::set_has_channel() {
  _has_bits_[0] |= 0x00000002u;
}
inline void control_msg::clear_has_channel() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void control_msg::clear_channel() {
  if (channel_ != NULL) channel_->::plumgrid::channel_info::Clear();
  clear_has_channel();
}
inline const ::plumgrid::channel_info& control_msg::channel() const {
  return channel_ != NULL ? *channel_ : *default_instance_->channel_;
}
inline ::plumgrid::channel_info* control_msg::mutable_channel() {
  set_has_channel();
  if (channel_ == NULL) channel_ = new ::plumgrid::channel_info;
  return channel_;
}
inline ::plumgrid::channel_info* control_msg::release_channel() {
  clear_has_channel();
  ::plumgrid::channel_info* temp = channel_;
  channel_ = NULL;
  return temp;
}
inline void control_msg::set_allocated_channel(::plumgrid::channel_info* channel) {
  delete channel_;
  channel_ = channel;
  if (channel) {
    set_has_channel();
  } else {
    clear_has_channel();
  }
}

// -------------------------------------------------------------------

// channel_list

// repeated .plumgrid.channel_info channel = 1;
inline int channel_list::channel_size() const {
  return channel_.size();
}
inline void channel_list::clear_channel() {
  channel_.Clear();
}
inline const ::plumgrid::channel_info& channel_list::channel(int index) const {
  return channel_.Get(index);
}
inline ::plumgrid::channel_info* channel_list::mutable_channel(int index) {
  return channel_.Mutable(index);
}
inline ::plumgrid::channel_info* channel_list::add_channel() {
  return channel_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::plumgrid::channel_info >&
channel_list::channel() const {
  return channel_;
}
inline ::google::protobuf::RepeatedPtrField< ::plumgrid::channel_info >*
channel_list::mutable_channel() {
  return &channel_;
}

// -------------------------------------------------------------------

// ack

// required int32 placeholder = 1;
inline bool ack::has_placeholder() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ack::set_has_placeholder() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ack::clear_has_placeholder() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ack::clear_placeholder() {
  placeholder_ = 0;
  clear_has_placeholder();
}
inline ::google::protobuf::int32 ack::placeholder() const {
  return placeholder_;
}
inline void ack::set_placeholder(::google::protobuf::int32 value) {
  set_has_placeholder();
  placeholder_ = value;
}

// -------------------------------------------------------------------

// chat

// optional string contents = 1;
inline bool chat::has_contents() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void chat::set_has_contents() {
  _has_bits_[0] |= 0x00000001u;
}
inline void chat::clear_has_contents() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void chat::clear_contents() {
  if (contents_ != &::google::protobuf::internal::kEmptyString) {
    contents_->clear();
  }
  clear_has_contents();
}
inline const ::std::string& chat::contents() const {
  return *contents_;
}
inline void chat::set_contents(const ::std::string& value) {
  set_has_contents();
  if (contents_ == &::google::protobuf::internal::kEmptyString) {
    contents_ = new ::std::string;
  }
  contents_->assign(value);
}
inline void chat::set_contents(const char* value) {
  set_has_contents();
  if (contents_ == &::google::protobuf::internal::kEmptyString) {
    contents_ = new ::std::string;
  }
  contents_->assign(value);
}
inline void chat::set_contents(const char* value, size_t size) {
  set_has_contents();
  if (contents_ == &::google::protobuf::internal::kEmptyString) {
    contents_ = new ::std::string;
  }
  contents_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* chat::mutable_contents() {
  set_has_contents();
  if (contents_ == &::google::protobuf::internal::kEmptyString) {
    contents_ = new ::std::string;
  }
  return contents_;
}
inline ::std::string* chat::release_contents() {
  clear_has_contents();
  if (contents_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = contents_;
    contents_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void chat::set_allocated_contents(::std::string* contents) {
  if (contents_ != &::google::protobuf::internal::kEmptyString) {
    delete contents_;
  }
  if (contents) {
    set_has_contents();
    contents_ = contents;
  } else {
    clear_has_contents();
    contents_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace plumgrid

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::plumgrid::control_msg_Type>() {
  return ::plumgrid::control_msg_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_datatype_2eproto__INCLUDED
