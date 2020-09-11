// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Shakehand.proto

#include "Shakehand.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
class ShakeHandEventDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ShakeHandEvent> _instance;
} _ShakeHandEvent_default_instance_;
class AuthenticationEventDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<AuthenticationEvent> _instance;
} _AuthenticationEvent_default_instance_;
static void InitDefaultsscc_info_AuthenticationEvent_Shakehand_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_AuthenticationEvent_default_instance_;
    new (ptr) ::AuthenticationEvent();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::AuthenticationEvent::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_AuthenticationEvent_Shakehand_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_AuthenticationEvent_Shakehand_2eproto}, {}};

static void InitDefaultsscc_info_ShakeHandEvent_Shakehand_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_ShakeHandEvent_default_instance_;
    new (ptr) ::ShakeHandEvent();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::ShakeHandEvent::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ShakeHandEvent_Shakehand_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_ShakeHandEvent_Shakehand_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Shakehand_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Shakehand_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Shakehand_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Shakehand_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ShakeHandEvent, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ShakeHandEvent, state_),
  PROTOBUF_FIELD_OFFSET(::ShakeHandEvent, src_name_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::AuthenticationEvent, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::AuthenticationEvent, node_type_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::ShakeHandEvent)},
  { 7, -1, sizeof(::AuthenticationEvent)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_ShakeHandEvent_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_AuthenticationEvent_default_instance_),
};

const char descriptor_table_protodef_Shakehand_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017Shakehand.proto\"1\n\016ShakeHandEvent\022\r\n\005s"
  "tate\030\001 \001(\r\022\020\n\010src_name\030\002 \001(\t\"(\n\023Authenti"
  "cationEvent\022\021\n\tnode_type\030\001 \001(\rb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_Shakehand_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_Shakehand_2eproto_sccs[2] = {
  &scc_info_AuthenticationEvent_Shakehand_2eproto.base,
  &scc_info_ShakeHandEvent_Shakehand_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Shakehand_2eproto_once;
static bool descriptor_table_Shakehand_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Shakehand_2eproto = {
  &descriptor_table_Shakehand_2eproto_initialized, descriptor_table_protodef_Shakehand_2eproto, "Shakehand.proto", 118,
  &descriptor_table_Shakehand_2eproto_once, descriptor_table_Shakehand_2eproto_sccs, descriptor_table_Shakehand_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_Shakehand_2eproto::offsets,
  file_level_metadata_Shakehand_2eproto, 2, file_level_enum_descriptors_Shakehand_2eproto, file_level_service_descriptors_Shakehand_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Shakehand_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_Shakehand_2eproto), true);

// ===================================================================

void ShakeHandEvent::InitAsDefaultInstance() {
}
class ShakeHandEvent::_Internal {
 public:
};

ShakeHandEvent::ShakeHandEvent()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ShakeHandEvent)
}
ShakeHandEvent::ShakeHandEvent(const ShakeHandEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  src_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from.src_name().empty()) {
    src_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.src_name_);
  }
  state_ = from.state_;
  // @@protoc_insertion_point(copy_constructor:ShakeHandEvent)
}

void ShakeHandEvent::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ShakeHandEvent_Shakehand_2eproto.base);
  src_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  state_ = 0u;
}

ShakeHandEvent::~ShakeHandEvent() {
  // @@protoc_insertion_point(destructor:ShakeHandEvent)
  SharedDtor();
}

void ShakeHandEvent::SharedDtor() {
  src_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ShakeHandEvent::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ShakeHandEvent& ShakeHandEvent::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ShakeHandEvent_Shakehand_2eproto.base);
  return *internal_default_instance();
}


void ShakeHandEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:ShakeHandEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  src_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  state_ = 0u;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ShakeHandEvent::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 state = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          state_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string src_name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_src_name(), ptr, ctx, "ShakeHandEvent.src_name");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool ShakeHandEvent::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:ShakeHandEvent)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // uint32 state = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &state_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string src_name = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_src_name()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->src_name().data(), static_cast<int>(this->src_name().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "ShakeHandEvent.src_name"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ShakeHandEvent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ShakeHandEvent)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ShakeHandEvent::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ShakeHandEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 state = 1;
  if (this->state() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(1, this->state(), output);
  }

  // string src_name = 2;
  if (this->src_name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->src_name().data(), static_cast<int>(this->src_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ShakeHandEvent.src_name");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->src_name(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ShakeHandEvent)
}

::PROTOBUF_NAMESPACE_ID::uint8* ShakeHandEvent::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ShakeHandEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 state = 1;
  if (this->state() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->state(), target);
  }

  // string src_name = 2;
  if (this->src_name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->src_name().data(), static_cast<int>(this->src_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ShakeHandEvent.src_name");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        2, this->src_name(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ShakeHandEvent)
  return target;
}

size_t ShakeHandEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ShakeHandEvent)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string src_name = 2;
  if (this->src_name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->src_name());
  }

  // uint32 state = 1;
  if (this->state() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->state());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ShakeHandEvent::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ShakeHandEvent)
  GOOGLE_DCHECK_NE(&from, this);
  const ShakeHandEvent* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ShakeHandEvent>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ShakeHandEvent)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ShakeHandEvent)
    MergeFrom(*source);
  }
}

void ShakeHandEvent::MergeFrom(const ShakeHandEvent& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ShakeHandEvent)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.src_name().size() > 0) {

    src_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.src_name_);
  }
  if (from.state() != 0) {
    set_state(from.state());
  }
}

void ShakeHandEvent::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ShakeHandEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ShakeHandEvent::CopyFrom(const ShakeHandEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ShakeHandEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ShakeHandEvent::IsInitialized() const {
  return true;
}

void ShakeHandEvent::InternalSwap(ShakeHandEvent* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  src_name_.Swap(&other->src_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(state_, other->state_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ShakeHandEvent::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void AuthenticationEvent::InitAsDefaultInstance() {
}
class AuthenticationEvent::_Internal {
 public:
};

AuthenticationEvent::AuthenticationEvent()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AuthenticationEvent)
}
AuthenticationEvent::AuthenticationEvent(const AuthenticationEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  node_type_ = from.node_type_;
  // @@protoc_insertion_point(copy_constructor:AuthenticationEvent)
}

void AuthenticationEvent::SharedCtor() {
  node_type_ = 0u;
}

AuthenticationEvent::~AuthenticationEvent() {
  // @@protoc_insertion_point(destructor:AuthenticationEvent)
  SharedDtor();
}

void AuthenticationEvent::SharedDtor() {
}

void AuthenticationEvent::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const AuthenticationEvent& AuthenticationEvent::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_AuthenticationEvent_Shakehand_2eproto.base);
  return *internal_default_instance();
}


void AuthenticationEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:AuthenticationEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  node_type_ = 0u;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* AuthenticationEvent::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 node_type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          node_type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool AuthenticationEvent::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:AuthenticationEvent)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // uint32 node_type = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &node_type_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:AuthenticationEvent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AuthenticationEvent)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void AuthenticationEvent::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AuthenticationEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 node_type = 1;
  if (this->node_type() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(1, this->node_type(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AuthenticationEvent)
}

::PROTOBUF_NAMESPACE_ID::uint8* AuthenticationEvent::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AuthenticationEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 node_type = 1;
  if (this->node_type() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->node_type(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AuthenticationEvent)
  return target;
}

size_t AuthenticationEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:AuthenticationEvent)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 node_type = 1;
  if (this->node_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->node_type());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AuthenticationEvent::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:AuthenticationEvent)
  GOOGLE_DCHECK_NE(&from, this);
  const AuthenticationEvent* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AuthenticationEvent>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:AuthenticationEvent)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:AuthenticationEvent)
    MergeFrom(*source);
  }
}

void AuthenticationEvent::MergeFrom(const AuthenticationEvent& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:AuthenticationEvent)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.node_type() != 0) {
    set_node_type(from.node_type());
  }
}

void AuthenticationEvent::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:AuthenticationEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AuthenticationEvent::CopyFrom(const AuthenticationEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:AuthenticationEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AuthenticationEvent::IsInitialized() const {
  return true;
}

void AuthenticationEvent::InternalSwap(AuthenticationEvent* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(node_type_, other->node_type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata AuthenticationEvent::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ShakeHandEvent* Arena::CreateMaybeMessage< ::ShakeHandEvent >(Arena* arena) {
  return Arena::CreateInternal< ::ShakeHandEvent >(arena);
}
template<> PROTOBUF_NOINLINE ::AuthenticationEvent* Arena::CreateMaybeMessage< ::AuthenticationEvent >(Arena* arena) {
  return Arena::CreateInternal< ::AuthenticationEvent >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
