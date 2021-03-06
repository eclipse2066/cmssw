#ifndef FWCore_ParameterSet_XORGroupDescription_h
#define FWCore_ParameterSet_XORGroupDescription_h

#include "FWCore/ParameterSet/interface/ParameterDescriptionNode.h"

#include "FWCore/Utilities/interface/value_ptr.h"

#include <memory>
#include <iosfwd>
#include <set>
#include <string>

namespace edm {

  class ParameterSet;
  class DocFormatHelper;

  class XORGroupDescription : public ParameterDescriptionNode {
  public:
    XORGroupDescription(ParameterDescriptionNode const& node_left,
                        ParameterDescriptionNode const& node_right);

    XORGroupDescription(std::auto_ptr<ParameterDescriptionNode> node_left,
                        ParameterDescriptionNode const& node_right);

    XORGroupDescription(ParameterDescriptionNode const& node_left,
                        std::auto_ptr<ParameterDescriptionNode> node_right);

    XORGroupDescription(std::auto_ptr<ParameterDescriptionNode> node_left,
                        std::auto_ptr<ParameterDescriptionNode> node_right);

    virtual ParameterDescriptionNode* clone() const {
      return new XORGroupDescription(*this);
    }

  private:

    virtual void checkAndGetLabelsAndTypes_(std::set<std::string> & usedLabels,
                                            std::set<ParameterTypes> & parameterTypes,
                                            std::set<ParameterTypes> & wildcardTypes) const;

    virtual void validate_(ParameterSet & pset,
                           std::set<std::string> & validatedLabels,
                           bool optional) const;

    virtual void writeCfi_(std::ostream & os,
                           bool & startWithComma,
                           int indentation,
                           bool & wroteSomething) const;

    virtual void print_(std::ostream & os,
                        bool optional,
                        bool writeToCfi,
                        DocFormatHelper & dfh);

    virtual bool hasNestedContent_() {
      return true;
    }

    virtual void printNestedContent_(std::ostream & os,
                                     bool optional,
                                     DocFormatHelper & dfh);

    virtual bool exists_(ParameterSet const& pset) const;

    virtual bool partiallyExists_(ParameterSet const& pset) const;

    virtual int howManyXORSubNodesExist_(ParameterSet const& pset) const;

    void throwMoreThanOneParameter() const;
    void throwAfterValidation() const;

    edm::value_ptr<ParameterDescriptionNode> node_left_;
    edm::value_ptr<ParameterDescriptionNode> node_right_;
  };
}
#endif
