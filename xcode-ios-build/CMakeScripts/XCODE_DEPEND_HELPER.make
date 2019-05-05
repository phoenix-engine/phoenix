# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Consumer.Debug:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Debug${EFFECTIVE_PLATFORM_NAME}/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Debug${EFFECTIVE_PLATFORM_NAME}/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/Debug/Consumer.build/$(OBJDIR)/arm64/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/Debug/Consumer.build/$(OBJDIR)/arm64e/libConsumer.a


PostBuild.Error.Debug:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Debug${EFFECTIVE_PLATFORM_NAME}/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Debug${EFFECTIVE_PLATFORM_NAME}/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/Debug/Error.build/$(OBJDIR)/arm64/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/Debug/Error.build/$(OBJDIR)/arm64e/libError.a


PostBuild.Consumer.Release:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Release${EFFECTIVE_PLATFORM_NAME}/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Release${EFFECTIVE_PLATFORM_NAME}/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/Release/Consumer.build/$(OBJDIR)/arm64/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/Release/Consumer.build/$(OBJDIR)/arm64e/libConsumer.a


PostBuild.Error.Release:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Release${EFFECTIVE_PLATFORM_NAME}/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Release${EFFECTIVE_PLATFORM_NAME}/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/Release/Error.build/$(OBJDIR)/arm64/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/Release/Error.build/$(OBJDIR)/arm64e/libError.a


PostBuild.Consumer.MinSizeRel:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/MinSizeRel${EFFECTIVE_PLATFORM_NAME}/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/MinSizeRel${EFFECTIVE_PLATFORM_NAME}/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/MinSizeRel/Consumer.build/$(OBJDIR)/arm64/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/MinSizeRel/Consumer.build/$(OBJDIR)/arm64e/libConsumer.a


PostBuild.Error.MinSizeRel:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/MinSizeRel${EFFECTIVE_PLATFORM_NAME}/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/MinSizeRel${EFFECTIVE_PLATFORM_NAME}/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/MinSizeRel/Error.build/$(OBJDIR)/arm64/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/MinSizeRel/Error.build/$(OBJDIR)/arm64e/libError.a


PostBuild.Consumer.RelWithDebInfo:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/RelWithDebInfo${EFFECTIVE_PLATFORM_NAME}/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/RelWithDebInfo${EFFECTIVE_PLATFORM_NAME}/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/RelWithDebInfo/Consumer.build/$(OBJDIR)/arm64/libConsumer.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/consumer/Phoenix.build/RelWithDebInfo/Consumer.build/$(OBJDIR)/arm64e/libConsumer.a


PostBuild.Error.RelWithDebInfo:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/RelWithDebInfo${EFFECTIVE_PLATFORM_NAME}/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/RelWithDebInfo${EFFECTIVE_PLATFORM_NAME}/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/RelWithDebInfo/Error.build/$(OBJDIR)/arm64/libError.a
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-ios-build/src/error/Phoenix.build/RelWithDebInfo/Error.build/$(OBJDIR)/arm64e/libError.a




# For each target create a dummy ruleso the target does not have to exist
