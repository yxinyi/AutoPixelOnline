// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_preserve_unknown_enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto;
namespace proto3_preserve_unknown_enum_unittest {
class MyMessage;
class MyMessageDefaultTypeInternal;
extern MyMessageDefaultTypeInternal _MyMessage_default_instance_;
class MyMessagePlusExtra;
class MyMessagePlusExtraDefaultTypeInternal;
extern MyMessagePlusExtraDefaultTypeInternal _MyMessagePlusExtra_default_instance_;
}  // namespace proto3_preserve_unknown_enum_unittest
PROTOBUF_NAMESPACE_OPEN
template<> ::proto3_preserve_unknown_enum_unittest::MyMessage* Arena::CreateMaybeMessage<::proto3_preserve_unknown_enum_unittest::MyMessage>(Arena*);
template<> ::proto3_preserve_unknown_enum_unittest::MyMessagePlusExtra* Arena::CreateMaybeMessage<::proto3_preserve_unknown_enum_unittest::MyMessagePlusExtra>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto3_preserve_unknown_enum_unittest {

enum MyEnum : int {
  FOO = 0,
  BAR = 1,
  BAZ = 2,
  MyEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MyEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MyEnum_IsValid(int value);
constexpr MyEnum MyEnum_MIN = FOO;
constexpr MyEnum MyEnum_MAX = BAZ;
constexpr int MyEnum_ARRAYSIZE = MyEnum_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MyEnum_descriptor();
template<typename T>
inline const std::string& MyEnum_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MyEnum>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MyEnum_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MyEnum_descriptor(), enum_t_value);
}
inline bool MyEnum_Parse(
    const std::string& name, MyEnum* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MyEnum>(
    MyEnum_descriptor(), name, value);
}
enum MyEnumPlusExtra : int {
  E_FOO = 0,
  E_BAR = 1,
  E_BAZ = 2,
  E_EXTRA = 3,
  MyEnumPlusExtra_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MyEnumPlusExtra_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MyEnumPlusExtra_IsValid(int value);
constexpr MyEnumPlusExtra MyEnumPlusExtra_MIN = E_FOO;
constexpr MyEnumPlusExtra MyEnumPlusExtra_MAX = E_EXTRA;
constexpr int MyEnumPlusExtra_ARRAYSIZE = MyEnumPlusExtra_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MyEnumPlusExtra_descriptor();
template<typename T>
inline const std::string& MyEnumPlusExtra_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MyEnumPlusExtra>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MyEnumPlusExtra_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MyEnumPlusExtra_descriptor(), enum_t_value);
}
inline bool MyEnumPlusExtra_Parse(
    const std::string& name, MyEnumPlusExtra* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MyEnumPlusExtra>(
    MyEnumPlusExtra_descriptor(), name, value);
}
// ===================================================================

class MyMessage :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto3_preserve_unknown_enum_unittest.MyMessage) */ {
 public:
  MyMessage();
  virtual ~MyMessage();

  MyMessage(const MyMessage& from);
  MyMessage(MyMessage&& from) noexcept
    : MyMessage() {
    *this = ::std::move(from);
  }

  inline MyMessage& operator=(const MyMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline MyMessage& operator=(MyMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MyMessage& default_instance();

  enum OCase {
    kOneofE1 = 5,
    kOneofE2 = 6,
    O_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MyMessage* internal_default_instance() {
    return reinterpret_cast<const MyMessage*>(
               &_MyMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MyMessage& a, MyMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(MyMessage* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MyMessage* New() const final {
    return CreateMaybeMessage<MyMessage>(nullptr);
  }

  MyMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MyMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MyMessage& from);
  void MergeFrom(const MyMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MyMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto3_preserve_unknown_enum_unittest.MyMessage";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto);
    return ::descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRepeatedEFieldNumber = 2,
    kRepeatedPackedEFieldNumber = 3,
    kRepeatedPackedUnexpectedEFieldNumber = 4,
    kEFieldNumber = 1,
    kOneofE1FieldNumber = 5,
    kOneofE2FieldNumber = 6,
  };
  // repeated .proto3_preserve_unknown_enum_unittest.MyEnum repeated_e = 2;
  int repeated_e_size() const;
  void clear_repeated_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnum repeated_e(int index) const;
  void set_repeated_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnum value);
  void add_repeated_e(::proto3_preserve_unknown_enum_unittest::MyEnum value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& repeated_e() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_repeated_e();

  // repeated .proto3_preserve_unknown_enum_unittest.MyEnum repeated_packed_e = 3 [packed = true];
  int repeated_packed_e_size() const;
  void clear_repeated_packed_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnum repeated_packed_e(int index) const;
  void set_repeated_packed_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnum value);
  void add_repeated_packed_e(::proto3_preserve_unknown_enum_unittest::MyEnum value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& repeated_packed_e() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_repeated_packed_e();

  // repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_packed_unexpected_e = 4;
  int repeated_packed_unexpected_e_size() const;
  void clear_repeated_packed_unexpected_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra repeated_packed_unexpected_e(int index) const;
  void set_repeated_packed_unexpected_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  void add_repeated_packed_unexpected_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& repeated_packed_unexpected_e() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_repeated_packed_unexpected_e();

  // .proto3_preserve_unknown_enum_unittest.MyEnum e = 1;
  void clear_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnum e() const;
  void set_e(::proto3_preserve_unknown_enum_unittest::MyEnum value);

  // .proto3_preserve_unknown_enum_unittest.MyEnum oneof_e_1 = 5;
  private:
  bool has_oneof_e_1() const;
  public:
  void clear_oneof_e_1();
  ::proto3_preserve_unknown_enum_unittest::MyEnum oneof_e_1() const;
  void set_oneof_e_1(::proto3_preserve_unknown_enum_unittest::MyEnum value);

  // .proto3_preserve_unknown_enum_unittest.MyEnum oneof_e_2 = 6;
  private:
  bool has_oneof_e_2() const;
  public:
  void clear_oneof_e_2();
  ::proto3_preserve_unknown_enum_unittest::MyEnum oneof_e_2() const;
  void set_oneof_e_2(::proto3_preserve_unknown_enum_unittest::MyEnum value);

  void clear_o();
  OCase o_case() const;
  // @@protoc_insertion_point(class_scope:proto3_preserve_unknown_enum_unittest.MyMessage)
 private:
  class _Internal;
  void set_has_oneof_e_1();
  void set_has_oneof_e_2();

  inline bool has_o() const;
  inline void clear_has_o();

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> repeated_e_;
  mutable std::atomic<int> _repeated_e_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> repeated_packed_e_;
  mutable std::atomic<int> _repeated_packed_e_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> repeated_packed_unexpected_e_;
  mutable std::atomic<int> _repeated_packed_unexpected_e_cached_byte_size_;
  int e_;
  union OUnion {
    OUnion() {}
    int oneof_e_1_;
    int oneof_e_2_;
  } o_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 _oneof_case_[1];

  friend struct ::TableStruct_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto;
};
// -------------------------------------------------------------------

class MyMessagePlusExtra :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra) */ {
 public:
  MyMessagePlusExtra();
  virtual ~MyMessagePlusExtra();

  MyMessagePlusExtra(const MyMessagePlusExtra& from);
  MyMessagePlusExtra(MyMessagePlusExtra&& from) noexcept
    : MyMessagePlusExtra() {
    *this = ::std::move(from);
  }

  inline MyMessagePlusExtra& operator=(const MyMessagePlusExtra& from) {
    CopyFrom(from);
    return *this;
  }
  inline MyMessagePlusExtra& operator=(MyMessagePlusExtra&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MyMessagePlusExtra& default_instance();

  enum OCase {
    kOneofE1 = 5,
    kOneofE2 = 6,
    O_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MyMessagePlusExtra* internal_default_instance() {
    return reinterpret_cast<const MyMessagePlusExtra*>(
               &_MyMessagePlusExtra_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(MyMessagePlusExtra& a, MyMessagePlusExtra& b) {
    a.Swap(&b);
  }
  inline void Swap(MyMessagePlusExtra* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MyMessagePlusExtra* New() const final {
    return CreateMaybeMessage<MyMessagePlusExtra>(nullptr);
  }

  MyMessagePlusExtra* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MyMessagePlusExtra>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MyMessagePlusExtra& from);
  void MergeFrom(const MyMessagePlusExtra& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MyMessagePlusExtra* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto);
    return ::descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRepeatedEFieldNumber = 2,
    kRepeatedPackedEFieldNumber = 3,
    kRepeatedPackedUnexpectedEFieldNumber = 4,
    kEFieldNumber = 1,
    kOneofE1FieldNumber = 5,
    kOneofE2FieldNumber = 6,
  };
  // repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_e = 2;
  int repeated_e_size() const;
  void clear_repeated_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra repeated_e(int index) const;
  void set_repeated_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  void add_repeated_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& repeated_e() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_repeated_e();

  // repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_packed_e = 3 [packed = true];
  int repeated_packed_e_size() const;
  void clear_repeated_packed_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra repeated_packed_e(int index) const;
  void set_repeated_packed_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  void add_repeated_packed_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& repeated_packed_e() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_repeated_packed_e();

  // repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_packed_unexpected_e = 4 [packed = true];
  int repeated_packed_unexpected_e_size() const;
  void clear_repeated_packed_unexpected_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra repeated_packed_unexpected_e(int index) const;
  void set_repeated_packed_unexpected_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  void add_repeated_packed_unexpected_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& repeated_packed_unexpected_e() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_repeated_packed_unexpected_e();

  // .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra e = 1;
  void clear_e();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra e() const;
  void set_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);

  // .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra oneof_e_1 = 5;
  private:
  bool has_oneof_e_1() const;
  public:
  void clear_oneof_e_1();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra oneof_e_1() const;
  void set_oneof_e_1(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);

  // .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra oneof_e_2 = 6;
  private:
  bool has_oneof_e_2() const;
  public:
  void clear_oneof_e_2();
  ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra oneof_e_2() const;
  void set_oneof_e_2(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value);

  void clear_o();
  OCase o_case() const;
  // @@protoc_insertion_point(class_scope:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra)
 private:
  class _Internal;
  void set_has_oneof_e_1();
  void set_has_oneof_e_2();

  inline bool has_o() const;
  inline void clear_has_o();

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> repeated_e_;
  mutable std::atomic<int> _repeated_e_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> repeated_packed_e_;
  mutable std::atomic<int> _repeated_packed_e_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> repeated_packed_unexpected_e_;
  mutable std::atomic<int> _repeated_packed_unexpected_e_cached_byte_size_;
  int e_;
  union OUnion {
    OUnion() {}
    int oneof_e_1_;
    int oneof_e_2_;
  } o_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 _oneof_case_[1];

  friend struct ::TableStruct_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MyMessage

// .proto3_preserve_unknown_enum_unittest.MyEnum e = 1;
inline void MyMessage::clear_e() {
  e_ = 0;
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnum MyMessage::e() const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessage.e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(e_);
}
inline void MyMessage::set_e(::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  
  e_ = value;
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessage.e)
}

// repeated .proto3_preserve_unknown_enum_unittest.MyEnum repeated_e = 2;
inline int MyMessage::repeated_e_size() const {
  return repeated_e_.size();
}
inline void MyMessage::clear_repeated_e() {
  repeated_e_.Clear();
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnum MyMessage::repeated_e(int index) const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(repeated_e_.Get(index));
}
inline void MyMessage::set_repeated_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  repeated_e_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_e)
}
inline void MyMessage::add_repeated_e(::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  repeated_e_.Add(value);
  // @@protoc_insertion_point(field_add:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_e)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
MyMessage::repeated_e() const {
  // @@protoc_insertion_point(field_list:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_e)
  return repeated_e_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
MyMessage::mutable_repeated_e() {
  // @@protoc_insertion_point(field_mutable_list:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_e)
  return &repeated_e_;
}

// repeated .proto3_preserve_unknown_enum_unittest.MyEnum repeated_packed_e = 3 [packed = true];
inline int MyMessage::repeated_packed_e_size() const {
  return repeated_packed_e_.size();
}
inline void MyMessage::clear_repeated_packed_e() {
  repeated_packed_e_.Clear();
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnum MyMessage::repeated_packed_e(int index) const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(repeated_packed_e_.Get(index));
}
inline void MyMessage::set_repeated_packed_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  repeated_packed_e_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_e)
}
inline void MyMessage::add_repeated_packed_e(::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  repeated_packed_e_.Add(value);
  // @@protoc_insertion_point(field_add:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_e)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
MyMessage::repeated_packed_e() const {
  // @@protoc_insertion_point(field_list:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_e)
  return repeated_packed_e_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
MyMessage::mutable_repeated_packed_e() {
  // @@protoc_insertion_point(field_mutable_list:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_e)
  return &repeated_packed_e_;
}

// repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_packed_unexpected_e = 4;
inline int MyMessage::repeated_packed_unexpected_e_size() const {
  return repeated_packed_unexpected_e_.size();
}
inline void MyMessage::clear_repeated_packed_unexpected_e() {
  repeated_packed_unexpected_e_.Clear();
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessage::repeated_packed_unexpected_e(int index) const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_unexpected_e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(repeated_packed_unexpected_e_.Get(index));
}
inline void MyMessage::set_repeated_packed_unexpected_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_packed_unexpected_e_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_unexpected_e)
}
inline void MyMessage::add_repeated_packed_unexpected_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_packed_unexpected_e_.Add(value);
  // @@protoc_insertion_point(field_add:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_unexpected_e)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
MyMessage::repeated_packed_unexpected_e() const {
  // @@protoc_insertion_point(field_list:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_unexpected_e)
  return repeated_packed_unexpected_e_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
MyMessage::mutable_repeated_packed_unexpected_e() {
  // @@protoc_insertion_point(field_mutable_list:proto3_preserve_unknown_enum_unittest.MyMessage.repeated_packed_unexpected_e)
  return &repeated_packed_unexpected_e_;
}

// .proto3_preserve_unknown_enum_unittest.MyEnum oneof_e_1 = 5;
inline bool MyMessage::has_oneof_e_1() const {
  return o_case() == kOneofE1;
}
inline void MyMessage::set_has_oneof_e_1() {
  _oneof_case_[0] = kOneofE1;
}
inline void MyMessage::clear_oneof_e_1() {
  if (has_oneof_e_1()) {
    o_.oneof_e_1_ = 0;
    clear_has_o();
  }
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnum MyMessage::oneof_e_1() const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessage.oneof_e_1)
  if (has_oneof_e_1()) {
    return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(o_.oneof_e_1_);
  }
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(0);
}
inline void MyMessage::set_oneof_e_1(::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  if (!has_oneof_e_1()) {
    clear_o();
    set_has_oneof_e_1();
  }
  o_.oneof_e_1_ = value;
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessage.oneof_e_1)
}

// .proto3_preserve_unknown_enum_unittest.MyEnum oneof_e_2 = 6;
inline bool MyMessage::has_oneof_e_2() const {
  return o_case() == kOneofE2;
}
inline void MyMessage::set_has_oneof_e_2() {
  _oneof_case_[0] = kOneofE2;
}
inline void MyMessage::clear_oneof_e_2() {
  if (has_oneof_e_2()) {
    o_.oneof_e_2_ = 0;
    clear_has_o();
  }
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnum MyMessage::oneof_e_2() const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessage.oneof_e_2)
  if (has_oneof_e_2()) {
    return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(o_.oneof_e_2_);
  }
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnum >(0);
}
inline void MyMessage::set_oneof_e_2(::proto3_preserve_unknown_enum_unittest::MyEnum value) {
  if (!has_oneof_e_2()) {
    clear_o();
    set_has_oneof_e_2();
  }
  o_.oneof_e_2_ = value;
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessage.oneof_e_2)
}

inline bool MyMessage::has_o() const {
  return o_case() != O_NOT_SET;
}
inline void MyMessage::clear_has_o() {
  _oneof_case_[0] = O_NOT_SET;
}
inline MyMessage::OCase MyMessage::o_case() const {
  return MyMessage::OCase(_oneof_case_[0]);
}
// -------------------------------------------------------------------

// MyMessagePlusExtra

// .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra e = 1;
inline void MyMessagePlusExtra::clear_e() {
  e_ = 0;
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessagePlusExtra::e() const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(e_);
}
inline void MyMessagePlusExtra::set_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  
  e_ = value;
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.e)
}

// repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_e = 2;
inline int MyMessagePlusExtra::repeated_e_size() const {
  return repeated_e_.size();
}
inline void MyMessagePlusExtra::clear_repeated_e() {
  repeated_e_.Clear();
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessagePlusExtra::repeated_e(int index) const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(repeated_e_.Get(index));
}
inline void MyMessagePlusExtra::set_repeated_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_e_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_e)
}
inline void MyMessagePlusExtra::add_repeated_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_e_.Add(value);
  // @@protoc_insertion_point(field_add:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_e)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
MyMessagePlusExtra::repeated_e() const {
  // @@protoc_insertion_point(field_list:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_e)
  return repeated_e_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
MyMessagePlusExtra::mutable_repeated_e() {
  // @@protoc_insertion_point(field_mutable_list:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_e)
  return &repeated_e_;
}

// repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_packed_e = 3 [packed = true];
inline int MyMessagePlusExtra::repeated_packed_e_size() const {
  return repeated_packed_e_.size();
}
inline void MyMessagePlusExtra::clear_repeated_packed_e() {
  repeated_packed_e_.Clear();
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessagePlusExtra::repeated_packed_e(int index) const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(repeated_packed_e_.Get(index));
}
inline void MyMessagePlusExtra::set_repeated_packed_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_packed_e_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_e)
}
inline void MyMessagePlusExtra::add_repeated_packed_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_packed_e_.Add(value);
  // @@protoc_insertion_point(field_add:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_e)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
MyMessagePlusExtra::repeated_packed_e() const {
  // @@protoc_insertion_point(field_list:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_e)
  return repeated_packed_e_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
MyMessagePlusExtra::mutable_repeated_packed_e() {
  // @@protoc_insertion_point(field_mutable_list:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_e)
  return &repeated_packed_e_;
}

// repeated .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra repeated_packed_unexpected_e = 4 [packed = true];
inline int MyMessagePlusExtra::repeated_packed_unexpected_e_size() const {
  return repeated_packed_unexpected_e_.size();
}
inline void MyMessagePlusExtra::clear_repeated_packed_unexpected_e() {
  repeated_packed_unexpected_e_.Clear();
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessagePlusExtra::repeated_packed_unexpected_e(int index) const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_unexpected_e)
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(repeated_packed_unexpected_e_.Get(index));
}
inline void MyMessagePlusExtra::set_repeated_packed_unexpected_e(int index, ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_packed_unexpected_e_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_unexpected_e)
}
inline void MyMessagePlusExtra::add_repeated_packed_unexpected_e(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  repeated_packed_unexpected_e_.Add(value);
  // @@protoc_insertion_point(field_add:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_unexpected_e)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
MyMessagePlusExtra::repeated_packed_unexpected_e() const {
  // @@protoc_insertion_point(field_list:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_unexpected_e)
  return repeated_packed_unexpected_e_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
MyMessagePlusExtra::mutable_repeated_packed_unexpected_e() {
  // @@protoc_insertion_point(field_mutable_list:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.repeated_packed_unexpected_e)
  return &repeated_packed_unexpected_e_;
}

// .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra oneof_e_1 = 5;
inline bool MyMessagePlusExtra::has_oneof_e_1() const {
  return o_case() == kOneofE1;
}
inline void MyMessagePlusExtra::set_has_oneof_e_1() {
  _oneof_case_[0] = kOneofE1;
}
inline void MyMessagePlusExtra::clear_oneof_e_1() {
  if (has_oneof_e_1()) {
    o_.oneof_e_1_ = 0;
    clear_has_o();
  }
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessagePlusExtra::oneof_e_1() const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.oneof_e_1)
  if (has_oneof_e_1()) {
    return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(o_.oneof_e_1_);
  }
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(0);
}
inline void MyMessagePlusExtra::set_oneof_e_1(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  if (!has_oneof_e_1()) {
    clear_o();
    set_has_oneof_e_1();
  }
  o_.oneof_e_1_ = value;
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.oneof_e_1)
}

// .proto3_preserve_unknown_enum_unittest.MyEnumPlusExtra oneof_e_2 = 6;
inline bool MyMessagePlusExtra::has_oneof_e_2() const {
  return o_case() == kOneofE2;
}
inline void MyMessagePlusExtra::set_has_oneof_e_2() {
  _oneof_case_[0] = kOneofE2;
}
inline void MyMessagePlusExtra::clear_oneof_e_2() {
  if (has_oneof_e_2()) {
    o_.oneof_e_2_ = 0;
    clear_has_o();
  }
}
inline ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra MyMessagePlusExtra::oneof_e_2() const {
  // @@protoc_insertion_point(field_get:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.oneof_e_2)
  if (has_oneof_e_2()) {
    return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(o_.oneof_e_2_);
  }
  return static_cast< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra >(0);
}
inline void MyMessagePlusExtra::set_oneof_e_2(::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra value) {
  if (!has_oneof_e_2()) {
    clear_o();
    set_has_oneof_e_2();
  }
  o_.oneof_e_2_ = value;
  // @@protoc_insertion_point(field_set:proto3_preserve_unknown_enum_unittest.MyMessagePlusExtra.oneof_e_2)
}

inline bool MyMessagePlusExtra::has_o() const {
  return o_case() != O_NOT_SET;
}
inline void MyMessagePlusExtra::clear_has_o() {
  _oneof_case_[0] = O_NOT_SET;
}
inline MyMessagePlusExtra::OCase MyMessagePlusExtra::o_case() const {
  return MyMessagePlusExtra::OCase(_oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto3_preserve_unknown_enum_unittest

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::proto3_preserve_unknown_enum_unittest::MyEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto3_preserve_unknown_enum_unittest::MyEnum>() {
  return ::proto3_preserve_unknown_enum_unittest::MyEnum_descriptor();
}
template <> struct is_proto_enum< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra>() {
  return ::proto3_preserve_unknown_enum_unittest::MyEnumPlusExtra_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum_2eproto
